#pragma once

class lerpingFloat {
public:
	lerpingFloat(float startCurrent, float speed) : m_current(startCurrent), m_target(startCurrent), m_speed(speed / 10.f) {}
	lerpingFloat() = default;
public:
	lerpingFloat& update(float speed = 0.f) {
		if (m_speed != speed && speed != 0.f) {
			m_speed = speed;
			if (m_speed != speed / 10.f)
				m_speed /= 10.f;
		}
		if (m_current != m_target) {
			m_current = m_current * (1 - m_speed) + m_target * m_speed;
		}
		else if (m_current > m_target - 0.0005 && m_current < m_target + 0.0005) {
			m_current = m_target;
		}
		return *this;
	}
public:
	lerpingFloat& setTarget(float newTarget) {
		m_target = newTarget;
		return *this;
	}
	lerpingFloat& setCurrent(float newCurrent) {
		m_current = newCurrent;
		return *this;
	}
public:
	float getCurrent() {
		return m_current;
	}
private:
	float m_target{};
	float m_current{};
	float m_speed{};
};