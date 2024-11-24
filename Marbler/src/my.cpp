#include "my.h"

void drawThickLine(const ofVec2f& start, const ofVec2f& end, float lineWidth) {
    // ���̕����x�N�g��
    ofVec2f direction = end - start;
    direction.normalize();

    // �@���x�N�g���i������������j
    ofVec2f normal(-direction.y, direction.x);
    normal *= lineWidth / 2.0;

    // �l�p�`��4�̒��_
    ofVec2f v1 = start + normal;
    ofVec2f v2 = start - normal;
    ofVec2f v3 = end - normal;
    ofVec2f v4 = end + normal;

    // �l�p�`��`��
    ofFill();
    ofBeginShape();
    ofVertex(v1);
    ofVertex(v2);
    ofVertex(v3);
    ofVertex(v4);
    ofEndShape(true); // true�͕����`����Ӗ�����
}

void drawThickLineWithRoundCaps(const ofVec2f& start, const ofVec2f& end, float lineWidth) {
    // ���̕����x�N�g��
    ofVec2f direction = end - start;
    direction.normalize();

    // �@���x�N�g���i������������j
    ofVec2f normal(-direction.y, direction.x);
    normal *= lineWidth / 2.0;

    // �l�p�`��4�̒��_
    ofVec2f v1 = start + normal;
    ofVec2f v2 = start - normal;
    ofVec2f v3 = end - normal;
    ofVec2f v4 = end + normal;

    // �l�p�`��`��
    ofFill();
    ofBeginShape();
    ofVertex(v1);
    ofVertex(v2);
    ofVertex(v3);
    ofVertex(v4);
    ofEndShape(true);

    // �ۂ��[�i�J�n�_�j
    ofDrawCircle(start, lineWidth / 2.0);

    // �ۂ��[�i�I���_�j
    ofDrawCircle(end, lineWidth / 2.0);
}
