#include <iostream>

template <typename T>
class Vector3 {
public:
    Vector3(T v1, T v2, T v3) {
        m_vec[0] = v1;
        m_vec[1] = v2;
        m_vec[2] = v3;
    }
    T getMax();
private:
    T m_vec[3];
};

template <typename T>
T Vector3<T>::getMax() {
    T temp = m_vec[0] > m_vec[1] ? m_vec[0] : m_vec[1];
    return temp > m_vec[2] ? temp : m_vec[2];
}

int main() {

    return 0;
}