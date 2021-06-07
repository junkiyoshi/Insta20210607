#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	auto radius = 300;
	auto deg_width = 9;
	auto deg_span = 5;
	auto height_span = 10;
	auto max_height = 1000;
	for (auto deg_start = 0; deg_start < 360; deg_start += deg_width + 1) {

		auto deg = deg_start;

		ofColor face_color, line_color;
		face_color.setHsb(ofMap(deg_start, 0, 360, 0, 255), 255, 255);;

		for (auto height = 0; height < max_height; height += height_span) {

			auto prev_noise_value  = ofNoise(radius * cos(deg_start * DEG_TO_RAD) * 0.005, radius * sin(deg_start * DEG_TO_RAD) * 0.005, (height - height_span) * 0.002 + ofGetFrameNum() * 0.02);
			auto noise_value = ofNoise(radius * cos(deg_start * DEG_TO_RAD) * 0.005, radius * sin(deg_start * DEG_TO_RAD) * 0.005, height * 0.002 + ofGetFrameNum() * 0.02);
			auto next_noise_value = ofNoise(radius * cos(deg_start * DEG_TO_RAD) * 0.005, radius * sin(deg_start * DEG_TO_RAD) * 0.005, (height + height_span) * 0.002 + ofGetFrameNum() * 0.02);

			if (noise_value < 0.5) {

				this->face.addVertex(glm::vec3(radius * cos((deg)* DEG_TO_RAD), height, radius * sin((deg)* DEG_TO_RAD)));
				this->face.addVertex(glm::vec3(radius * cos((deg + deg_width) * DEG_TO_RAD), height, radius * sin((deg + deg_width) * DEG_TO_RAD)));
				this->face.addVertex(glm::vec3(radius * cos((deg + deg_span + deg_width) * DEG_TO_RAD), height + height_span, radius * sin((deg + deg_span + deg_width) * DEG_TO_RAD)));
				this->face.addVertex(glm::vec3(radius * cos((deg + deg_span) * DEG_TO_RAD), height + height_span, radius * sin((deg + deg_span) * DEG_TO_RAD)));

				this->line.addVertex(glm::vec3(radius * cos((deg)* DEG_TO_RAD), height, radius * sin((deg)* DEG_TO_RAD)));
				this->line.addVertex(glm::vec3(radius * cos((deg + deg_width) * DEG_TO_RAD), height, radius * sin((deg + deg_width) * DEG_TO_RAD)));
				this->line.addVertex(glm::vec3(radius * cos((deg + deg_span + deg_width) * DEG_TO_RAD), height + height_span, radius * sin((deg + deg_span + deg_width) * DEG_TO_RAD)));
				this->line.addVertex(glm::vec3(radius * cos((deg + deg_span) * DEG_TO_RAD), height + height_span, radius * sin((deg + deg_span) * DEG_TO_RAD)));

				this->face.addColor(ofColor(0));
				this->face.addColor(ofColor(0));
				this->face.addColor(ofColor(0));
				this->face.addColor(ofColor(0));

				this->line.addColor(face_color);
				this->line.addColor(face_color);
				this->line.addColor(face_color);
				this->line.addColor(face_color);

				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 3);
				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 4);

				this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 4);
				this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 3);

				if (height >= max_height - height_span || next_noise_value > 0.5) {

					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (height < height_span || prev_noise_value > 0.5) {

					this->line.addIndex(this->line.getNumVertices() - 3); this->line.addIndex(this->line.getNumVertices() - 4);
				}
			}

			deg += deg_span;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofTranslate(0, -500, 0);

	this->face.drawFaces();
	this->line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}