#include "my.h"

void drawThickLine(const ofVec2f& start, const ofVec2f& end, float lineWidth) {
    // 線の方向ベクトル
    ofVec2f direction = end - start;
    direction.normalize();

    // 法線ベクトル（直交する方向）
    ofVec2f normal(-direction.y, direction.x);
    normal *= lineWidth / 2.0;

    // 四角形の4つの頂点
    ofVec2f v1 = start + normal;
    ofVec2f v2 = start - normal;
    ofVec2f v3 = end - normal;
    ofVec2f v4 = end + normal;

    // 四角形を描画
    ofFill();
    ofBeginShape();
    ofVertex(v1);
    ofVertex(v2);
    ofVertex(v3);
    ofVertex(v4);
    ofEndShape(true); // trueは閉じた形状を意味する
}

void drawThickLineWithRoundCaps(const ofVec2f& start, const ofVec2f& end, float lineWidth) {
    // 線の方向ベクトル
    ofVec2f direction = end - start;
    direction.normalize();

    // 法線ベクトル（直交する方向）
    ofVec2f normal(-direction.y, direction.x);
    normal *= lineWidth / 2.0;

    // 四角形の4つの頂点
    ofVec2f v1 = start + normal;
    ofVec2f v2 = start - normal;
    ofVec2f v3 = end - normal;
    ofVec2f v4 = end + normal;

    // 四角形を描画
    ofFill();
    ofBeginShape();
    ofVertex(v1);
    ofVertex(v2);
    ofVertex(v3);
    ofVertex(v4);
    ofEndShape(true);

    // 丸い端（開始点）
    ofDrawCircle(start, lineWidth / 2.0);

    // 丸い端（終了点）
    ofDrawCircle(end, lineWidth / 2.0);
}
