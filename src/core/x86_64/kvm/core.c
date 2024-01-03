#include "core.h"

#include <linux/kvm.h>
#include <linux/kvm_para.h>

#include <unistd.h>
#include <fcntl.h>

#include <stdlib.h>

int kvm = -1;

bool_t vp_mem_res_new()                             { return true_t; }
void   vp_mem_res_del()                             { return       ; }

void*  vp_mem_new    (mem_res* par, u64_t par_size) { return malloc(par_size); }
void   vp_mem_del    (mem_res* par, void* par_del)  { free(par_del); }

mem_res vp_mem_res             = {
	.on_new     = &vp_mem_res_new,
	.on_del     = &vp_mem_res_del,

	.on_mem_new = &vp_mem_new    ,
	.on_mem_del = &vp_mem_del
};

bool_t
    core_init()                                   {
        kvm = open("/dev/kvm", O_RDWR | O_CLOEXEC);
        if (!kvm) return false_t;

        mem_res_new(&vp_mem_res, 0);
	    set_mem_res(&vp_mem_res)   ;
        return kvm;
}

void
    core_deinit() {
        close(kvm);
}