#!/usr/bin/env ruby
#
# https://github.com/riscv/riscv-opcodes.git
#

FieldInfo = Struct.new :hi, :lo, :name, :value
class FieldInfo
  def bin_str()
    width = hi - lo + 1
    if name
      "<%d.%s>" % [ width, name ]
    else
      sprintf "%0*b", width, value
    end
  end
  def to_s
    "<%d:%d #{name} #{value}>" % [ hi, lo ]
  end
end
class InstInfo
  attr_reader :name, :pseudo, :fields
  def initialize(name, pseudo, fields)
    @name, @pseudo = name, pseudo
    @fields = fields.sort_by{ |f| f.hi }.reverse
  end
  def binary_string
    @fields.map{ |f| f.bin_str }.join('')
  end
end
class String
  def to_int
    if self =~ /^0[xX](\h+)/
      $1.to_i(16)
    elsif self =~ /^0[bB]([01]+)/
      $1.to_i(2)
    else
      self.to_i
    end
  end
end

def init_arglut
  arglut = {}
  arglut['rd'] = [11,7]
  arglut['rs1'] = [19,15]
  arglut['rs2'] = [24,20]
  arglut['rs3'] = [31,27]
  arglut['aqrl'] = [26,25]
  arglut['fm'] = [31,28]
  arglut['pred'] = [27,24]
  arglut['succ'] = [23,20]
  arglut['rm'] = [14,12]
  arglut['funct3'] = [14,12]
  arglut['imm20'] = [31,12]
  arglut['jimm20'] = [31,12]
  arglut['imm12'] = [31,20]
  arglut['imm12hi'] = [31,25]
  arglut['bimm12hi'] = [31,25]
  arglut['imm12lo'] = [11,7]
  arglut['bimm12lo'] = [11,7]
  arglut['zimm'] = [19,15]
  arglut['shamt'] = [25,20]
  arglut['shamtw'] = [24,20]

  # for vectors
  arglut['vd'] = [11,7]
  arglut['vs3'] = [11,7]
  arglut['vs1'] = [19,15]
  arglut['vs2'] = [24,20]
  arglut['vm'] = [25,25]
  arglut['wd'] = [26,26]
  arglut['amoop'] = [31,27]
  arglut['nf'] = [31,29]
  arglut['simm5'] = [19,15]
  arglut['zimm11'] = [30,20]

  arglut.map{ |k,v| [k, FieldInfo.new(v[0], v[1], k, nil) ] }.to_h
end

def parse_opcode_files(arglut)
  insts = []
  ARGF.each do |line|
    line = line.sub(/#.*$/, '').strip
    next if line.empty?
    fields = line.split
    name = fields.shift
    pseudo = name[0] == '@'
    name.delete_prefix!('@')

    fields = fields.map do |field|
      if field =~ /^\w+$/
        fail if not arglut[field]
        arglut[field].clone
      elsif field =~ /(\d+)(\.\.)?(\d+)?=(\w+)/
        hi, lo, val = $1.to_i, $3, $4.to_int
        lo = lo ? lo.to_i : hi
        FieldInfo.new hi, lo, nil, val
      else
        fail
        nil
      end
    end
    insts << InstInfo.new(name, pseudo, fields)
  end
  insts
end

def print_insts(insts)
  insts.each do |inst|
    puts ""
    puts "INST(#{inst.name}, #{inst.binary_string}) {"
    puts "    EXECUTE() {"
    puts "    }"
    puts "}"
  end
end

arglut = init_arglut()
insts = parse_opcode_files(arglut)
print_insts(insts)

