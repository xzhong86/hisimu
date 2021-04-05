
#include "../rv64-cpu.h"
#include <assert.h>
#include <stdio.h>

/*<%
sout = StringIO.new 
isa.insts.each{ |i| i.gen_decode_exec_fun(sout, true) } 
func_decl = sout.string 
%>*/

<%= func_decl %> ;

typedef void (exec_func_t)(CPUState *, uint32_t);
struct inst_info {
    uint32_t mask;
    uint32_t match;
    exec_func_t *func;
};

static struct inst_info g_riscv_insts[] = {
    <%= isa.insts.map{|i| "{ 0x%08x, 0x%08x, riscv_decode_exec_%s }" % [ i.mask_val, i.match_val, i.c_name ] }.join(",\n") %>
};


void riscv_decode_exec_inst(CPUState *cpu, uint32_t code)
{
    int insts_arr_size = sizeof(g_riscv_insts) / sizeof(g_riscv_insts[0]);
    for (int i = 0; i < insts_arr_size; i++) {
        struct inst_info *info = &g_riscv_insts[i];
        if ((info->mask & code) == info->match) {
            info->func(cpu, code);
            return;
        }
    }
    printf("unknown inst pc=%lx, code=%x\n", cpu->pc, code);
    assert(0);
}
