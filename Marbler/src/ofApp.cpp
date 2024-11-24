#include "ofApp.h"
#include "my.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowShape(WIDTH, HEIGHT);
	ofSetFrameRate(60);

	ofSetBackgroundAuto(false);

	if (!defaultImage.loadImage("default.png"))
		ofLogError() << "ロード失敗" << endl;

	// ブラー用シェーダー
	fbo1.allocate(WIDTH, HEIGHT, GL_RGBA);
	fbo2.allocate(WIDTH, HEIGHT, GL_RGBA);
	blurHorizontal.load("blurHorizontal");
	blurVertical.load("blurVertical");


	// フレームバッファ
	fbo.allocate(WIDTH, HEIGHT, GL_RGBA);
	fbo.begin();
	defaultImage.draw(0, 0, WIDTH, HEIGHT);
	defaultImage.draw(0, 0, WIDTH, HEIGHT);
	fbo.end();

	// ofPixels表示用
	texture.allocate(WIDTH, HEIGHT, GL_RGBA);

	// マップ
	map.allocate(WIDTH, HEIGHT, GL_RGBA);
	map.begin();
	ofBackground(128);
	map.end();

	openCvMap.allocate(WIDTH, HEIGHT);


	printf("begin\n");
}

//--------------------------------------------------------------
void ofApp::update() {
	time = ofGetFrameNum();
	printf("%f\n", ofGetFrameRate());

	prevX = ofGetMouseX();
	prevY = ofGetMouseY();


	// フェード・ブラー

	//map.readToPixels(pixels);
	//openCvMap.setFromPixels(pixels);
	//openCvMap.blurGaussian(3);
	//openCvMap.draw(0, 0);
	
	fbo2.begin();
	blurHorizontal.begin();
	blurHorizontal.setUniformTexture("tex0", fbo1.getTexture(), 80);
	blurHorizontal.setUniform1f("blurAmount", 40);
	blurHorizontal.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	// fbo1.draw(0, 0);
	map.draw(0, 0, WIDTH, HEIGHT);
	blurHorizontal.end();
	fbo2.end();

	// 縦方向のブラー
	fbo1.begin();
	blurVertical.begin();
	blurVertical.setUniformTexture("tex0", fbo2.getTexture(), 80);
	blurVertical.setUniform1f("blurAmount", 40);
	blurVertical.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	fbo2.draw(0, 0);
	blurVertical.end();
	fbo1.end();

	map.begin();
	fbo1.draw(0, 0, WIDTH, HEIGHT);
	map.end();

	ofSetColor(128, 32);
	if (time % 15 == 0) {
		ofSetColor(128, 128);
	}

	ofRect(0, 0, WIDTH, HEIGHT);
	map.end();


	// マーブリング
	fbo.readToPixels(pixels);
	int numChannnels = pixels.getNumChannels();

	ofPixels pixels2;
	pixels2.allocate(WIDTH, HEIGHT, GL_RGBA);
	fbo.readToPixels(pixels2);

	ofPixels mapPixels;
	map.readToPixels(mapPixels);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			int i = (x + y * WIDTH) * numChannnels;

			int moveX = x - (mapPixels[i] - 128);
			int moveY = y - (mapPixels[i + 1] - 128);

			moveX = constrain(moveX, 0, WIDTH - 1);
			moveY = constrain(moveY, 0, HEIGHT - 1);

			int move = (moveX + WIDTH * moveY) * numChannnels;

			pixels2[i] = pixels[move];
			pixels2[i + 1] = pixels[move + 1];
			pixels2[i + 2] = pixels[move + 2];
		}
	}

	fbo.begin();
	texture.loadData(pixels2);
	texture.draw(0, 0);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {
	fbo.draw(0, 0, WIDTH, HEIGHT);

	map.draw(0, 0, WIDTH / 2, HEIGHT / 2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	fbo.begin();
	defaultImage.draw(0, 0);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	printf("dragged\n");

	// マップを更新
	map.begin();

	ofSetLineWidth(8.0f);
	ofNoFill();
	ofSetColor(abs(x - prevX), abs(y - prevY), 0);

	drawThickLineWithRoundCaps(ofVec2f(prevX, prevY), ofVec2f(x, y), 40); // 線の幅を10pxに設定

	// ofDrawLine(prevX, prevY, x, y);
	map.end();

	prevX = x;
	prevY = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
