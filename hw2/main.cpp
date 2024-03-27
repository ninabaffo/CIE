// Name: Nina Baffo
// Date: 9/12/22
// Course: ENGR 2730
// Description: Create a box class and a main program to test your box class

#include <iostream>

using namespace std;

// Box class
class Box {
public:
    // default value. Make sure to use input, not m_
    explicit Box(float width = 1, float height = 1, float depth = 1) {
        setWidth(width);
        setHeight(height);
        setDepth(depth);
        setVolume(width, depth, height);
        setSurfaceArea(width, depth, height);
    }

    double getWidth() const {return m_width;}
    double getHeight() const {return m_height;}
    double getDepth() const {return m_depth;}
    double getVolume() const {return m_volume;}
    double getSurfaceArea() const {return m_surfaceArea;}

    // setWidth() function returns the width of the box. If it's less than one, returns 1.0.
    void setWidth(const double width) {
        if (width >= 1.0) {
            m_width = width;
        }
        else {
            m_width = 1.0;
        }
    }
    // setDepth() function returns the depth of the box. If it's less than one, returns 1.0.
    void setDepth(const double depth) {
        if (depth >= 1.0) {
            m_depth = depth;
        } else {
            m_depth = 1.0;
        }
    }
    // setHeight() function returns the height of the box. If it's less than one, returns 1.0.
    void setHeight(const double height) {
        if (height >= 1.0) {
            m_height = height;
        } else {
            m_height = 1.0;
        }
    }

    // getVolume () function returns the volume of the box
    void setVolume(const float width, const float depth, const float height) {
        m_volume = (m_width*m_depth*m_height);

    }
    // getSurfaceArea () function returns the surface area of the box
    void setSurfaceArea(const float width, const float depth, const float height) {
        m_surfaceArea = 2*(m_depth*m_width + m_depth*m_height + m_height*m_width);
    }

private:
    float m_width, m_depth, m_height, m_volume, m_surfaceArea;
};

int main() {
    // create an object of Box class.
    Box box1;
    cout << "Expected box1.setWidth() = 1. Actual = " << box1.getWidth() << endl;

    Box box2;
    box2.setWidth(20);
    cout << "Expected box2.setWidth() = 20. Actual = " << box2.getWidth() << endl;

    Box box3;
    box3.setHeight(10);
    box3.setDepth(15);
    cout << "Expected box3.setHeight() = 10. Actual = " << box3.getHeight() << endl;
    cout << "Expected box3.setDepth() = 15. Actual = " << box3.getDepth() << endl;

    Box box4(10, 10, 15);
    cout << "Expected box4.getSurfaceArea() = 800. Actual = " << box4.getSurfaceArea() << endl;
    cout << "Expected box4.getVolume() = 1500. Actual = " << box4.getVolume() << endl;

    return 0;
}
