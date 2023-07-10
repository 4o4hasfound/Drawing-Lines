#ifndef _VECTOR_H_
#define _VECTOR_H_

struct vec2 {
	vec2() {

	};
	vec2(float a): x(a), y(a) {

	};
	vec2(float a, float b) : x(a), y(b) {

	};
	vec2(const vec2& a) : x(a.x), y(a.y) {

	};

	float x = 0;
	float y = 0;

	vec2& operator+=(const vec2& a) {
		x += a.x;
		y += a.y;
		return *this;
	}
	vec2& operator-=(const vec2& a) {
		x -= a.x;
		y -= a.y;
		return *this;
	}
	vec2& operator+=(float a) {
		x += a;
		y += a;
		return *this;
	}
	vec2& operator-=(float a) {
		x -= a;
		y -= a;
		return *this;
	}

	vec2 operator+(const vec2& a) const {
		vec2 ret = *this;
		return ret += a;
	}
	vec2 operator-(const vec2& a) const {
		vec2 ret = *this;
		return ret -= a;
	}
	vec2 operator+(float a) const {
		vec2 ret = *this;
		return ret += a;
	}
	vec2 operator-(float a) const {
		vec2 ret = *this;
		return ret -= a;
	}

};



#endif