require 'ISAParser'

require 'optparse'
require 'ostruct'
require 'erb'

class ISAParser::ISAInstInfo
  attr_accessor :class

  def gen_decode(out, dec_info = nil)
    bitfield = decode_code ? @bitfield : @class.bitfield
    fields_names = []
    (@bitfield.fields + @class.bitfield.fields).each do |field|
      name = field.name
      if name and not fields_names.include?(name)
        out.puts "uint32 %s = EXTRACT_BITS(inst_code, %d, %d);" % [ name, field.lo, field.width ]
        fields_names << name
      end
    end

    out.puts "int32 simm32 = 0;"
    out.puts "uint32 uimm32 = 0;"

    out.puts(decode_code || @class.decode_code) # decode code

    if dec_info
      info_fields = %w[ rd rs1 rs2 ]
      bitfield.fields.each do |field|
        name = field.name
        if name and info_fields.include?(name)
          out.puts "%s.%s = %s;" % [ dec_info, name, name ]
        end
      end
      out.puts "if (simm32) #{dec_info}.simm32 = simm32;"
      out.puts "if (uimm32) #{dec_info}.uimm32 = uimm32;"
    end
  end
  def gen_decode_fun(decl = false)
    func = "void riscv_decode_#{c_name}(uint32 inst_code, struct dec_info *info)"
    if decl
      out.puts "extern #{func};"
    else
      out.puts "#{func}\n{"
      gen_decode(out, "info")
      out.puts "}"
    end
  end
  def gen_decode_exec_fun(out, decl = false)
    func = "void riscv_decode_exec_#{c_name}(CPUState *cpu, uint32_t inst_code)"
    if decl
      out.puts "extern #{func};"
    else
      out.puts "#{func}\n{"
      gen_decode(out)
      out.puts execute_code()
      out.puts "}"
    end
  end
end

class RiscvISAInfo
  attr_reader :insts
  def initialize(insts)
    @insts   = insts.select{ |i| i.type == 'INST' }
    @classes = insts.select{ |i| i.type == 'INST_CLASS' }.map{ |i| [i.name, i] }.to_h
    setup_insts_class()
  end

  def setup_insts_class()
    @insts.each do |inst|
      fields = inst.bitfield.fields.map{ |f| f.name }
      case
      when fields.include?('imm20')     then _class = 'u_type'
      when fields.include?('imm12')     then _class = 'i_type'
      when fields.include?('imm12hi')   then _class = 's_type'
      when fields.include?('jimm20')    then _class = 'j_type'
      when fields.include?('bimm12hi')  then _class = 'b_type'
      when inst.name =~ /ecall|ebread/  then _class = 'i_type'
      #when f.name == 'fence'
      else _class = 'r_type'
      end
      inst.class = @classes[_class]
    end
  end

end

def gen_decode_file(out, isa)
end

def gen_decode_exec_file(out, isa)
  $opts.headers.each { |h| out.puts "#include <#{h}>" }
  isa.insts.each{ |inst| inst.gen_decode_exec_fun(out); out.puts "" }
end

def gen_by_temp(out, isa)
  b = binding
  erb_out = ""
  erb = ERB.new(IO.read($opts.temp), nil, nil, "erb_out")
  erb.result(b)
  out.puts erb_out
end

# main
$opts = OpenStruct.new
$opts.headers = []
OptionParser.new do |op|
  op.banner = "gen-c-code.rb"
  op.on('--headers HEADER[,HEADER]', "gen include header") { |hs| $opts.headers += hs.split(',')}
  op.on('-T', '--temp TEMP', 'template file') { |t| $opts.temp = t }
  op.on('-G', '--gen TYPE', 'generate file of TYPE') { |t| $opts.gtype = t }
  op.on('-o', '--output FILE', "set output file") { |f| $opts.out = f }
end.parse!

dir = File.dirname __FILE__

parser = ISAParser.new
parser.scan_file(dir + '/op-class.def')
parser.scan_file(dir + '/op-01-rv32i.def')

isa = RiscvISAInfo.new(parser.insts)

out = $opts.out ? File.open($opts.out, 'w') : $stdout

if $opts.headers.empty?
  $opts.headers = [ "arch/riscv/cpu.h", "arch/riscv/isa-helper.h" ]
end


if $opts.temp
  gen_by_temp(out, isa)
end

if $opts.gtype
  eval "gen_#{$opts.gtype}_file(out, isa)"
  #gen_decode_exec_file(out, isa)
end


