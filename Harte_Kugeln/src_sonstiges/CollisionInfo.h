/*
 * CollisionInfo.h
 *
 *  Created on: Jan 22, 2015
 *      Author: maud
 */

#ifndef SRC_SONSTIGES_COLLISIONINFO_H_
#define SRC_SONSTIGES_COLLISIONINFO_H_

template<unsigned DIM>
struct CollisionInfo {
	MatVec<velocityT,DIM> delta_v_collision;
	MatVec<lengthT,DIM> delta_p_collision;
	bool collision;
	timeT system_time;
};



#endif /* SRC_SONSTIGES_COLLISIONINFO_H_ */
