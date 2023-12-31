#ifndef __CORE_KVM_MAP_KEY_H__
#define __CORE_KVM_MAP_KEY_H__

#include <obj.h>
#include <map.h>

extern map_key *vp_map_key_t;

bool_t  vp_map_eq(struct vp_map*, struct vp_map*);
bool_t  vp_map_lt(struct vp_map*, struct vp_map*);
bool_t  vp_map_gt(struct vp_map*, struct vp_map*);

#endif