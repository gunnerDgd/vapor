#include <vp/vp.h>
#include <stdio.h>

vp_main() {
    vp_root root = make (vp_root_t) from (1, 4);
    vp_node node0 = vp_root_node(root , 0)   ;
    vp_cpu  cpu0  = vp_node_cpu (node0, 0)   ;
    vp_cpu  cpu1  = vp_node_cpu (node0, cpu0);
    vp_cpu  cpu2  = vp_node_cpu (node0, cpu1);
    vp_cpu  cpu3  = vp_node_cpu (node0, cpu2);
    printf ("Hello VM !!\n");
}