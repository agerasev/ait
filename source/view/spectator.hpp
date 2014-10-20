#ifndef SPECTATOR_H
#define SPECTATOR_H

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>

class Spectator
{
private:
	vec2 pos = nullvec2;
	mat2 ori = mat2{0,1e-2,1e-2,0};
public:
	void setPos(const vec2 &p)
	{
		pos = p;
	}
	void setOri(const mat2 &o)
	{
		ori = o;
	}
	const vec2 &getPos() const
	{
		return pos;
	}
	const mat2 &getOri() const
	{
		return ori;
	}
	void addPos(const vec2 &dp)
	{
		pos += dp;
	}
	void multOri(const mat2 &mo)
	{
		ori = ori*mo;
	}
};

#endif // SPECTATOR_H
