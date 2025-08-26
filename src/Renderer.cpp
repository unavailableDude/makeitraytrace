#include "../include/Renderer.hpp"

#include <iostream>
#include <math.h>

// glm
#include <glm/ext/matrix_float4x4.hpp>// mat4
#include <glm/ext/matrix_transform.hpp>

#include "Sphere.hpp"
#include "Ray.hpp"
#include "RayHit.hpp"
#include "Vec4.hpp"
#include "PointLight.hpp"
#include "OpenGLLayer.hpp"

#include "ShaderLoader.hpp"

#include "CommonMacros.hpp"


namespace MIRT {


Color4 ComputeLighting(const RayHit& rayHit, const PointLight& light, const Vec4& viewDir);


Renderer::Renderer(uint16_t width = 480, uint16_t height = 320)
    : _width(width),
      _height(height),
      _aspectRatio(float(width) / float(height)),
      _shaderProgram("../Shaders/VertexShader1.vert", "../Shaders/FragmentShader1.frag"),
      _computeShaderProgram("../Shaders/RaytracerCompute1.comp"),
      _lastFrameDeltaTime(0) {}

void Renderer::MakeArt() {
	// // create sphere in the middle
	// Sphere sphere1 = Sphere();
	// glm::mat4 translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 0.0f, 0.0f));
	// glm::mat4 scaling = glm::scale(glm::identity<glm::mat4>(), glm::vec3(5.0f, 5.0f, 5.0f));
	// sphere1.SetTransform(glm::transpose(translation * scaling));// convert it to row-major
	// Material material1 = Material();
	// material1.SetSurfaceColor(Color4(1.0f, 1.0f, 1.0f));
	// sphere1.SetMaterial(material1);

	// // create a point light above the sphere
	// PointLight light1 = PointLight(Color4(1.0f, 1.0f, 1.0f, 1.0f), Vec4(0.0f, 10.0f, 0.0f, 1.0f));

	// Material materialBG = Material();
	// materialBG.SetSurfaceColor(Color4(0.2f, 0.2f, 0.2f, 1.0f));


	// // draw
	// std::vector<Color4> pixels(_width * _height, Color4(1.0f, 0.0f, 1.0f, 1.0f));
	// for(uint16_t y = 0; y < _height; ++y) {
	// 	for(uint16_t x = 0; x < _width; ++x) {
	// 		Color4 currColor(0.0f, 0.0f, 0.0f, 1.0f);
	// 		Vec4 rayOrigin = Vec4(0.0f, 0.0f, -100.0f, 1.0f);

	// 		float halfW = (_width / 2);
	// 		float halfH = (_height / 2);

	// 		Vec4 pixelPos = Vec4(float(x - halfW), float(y - halfH), -90.0f, 1.0f);
	// 		pixelPos._x /= halfW;
	// 		pixelPos._y /= halfH * _aspectRatio;
	// 		Vec4 pixelDir = pixelPos - rayOrigin;

	// 		Ray ray = Ray(MakePoint(rayOrigin), MakeDir(pixelDir));

	// 		std::vector<RayHit> hits1 = sphere1.Intersect(ray);
	// 		std::vector<RayHit> allHits;
	// 		allHits.insert(allHits.end(), hits1.begin(), hits1.end());

	// 		if(!allHits.empty()) {
	// 			const RayHit& hit = FrontHit(allHits);
	// 			currColor = ComputeLighting(hit, light1, rayOrigin);
	// 		} else
	// 			currColor = materialBG.SurfaceColor();
	// 		pixels[y * _width + x] = currColor;
	// 	}
	// }

	auto renderStartTime = std::chrono::high_resolution_clock::now();
	GLCALL(glDisable(GL_CULL_FACE);)
	GLCALL(glDisable(GL_DEPTH_TEST);)
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, _fbo);)
	GLCALL(glViewport(0, 0, _width, _height);)
	GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f);)
	GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);)

	// raytrace, compute the pixels
	_computeShaderProgram.Use();
	_computeShaderProgram.SetUniform2f("uImageSize", Vec4(float(_width), float(_height), 0.0f, 0.0f));
	_computeShaderProgram.SetUniform1i("uNumSpheres", _currentScene.GetSpheres().size());

	// GLCALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, _SphereSSBO));
	// GLCALL(glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Sphere) * _currentScene.GetSpheres().size(),
	// _currentScene.GetSpheres().data(), GL_DYNAMIC_READ)); GLCALL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1,
	// _SphereSSBO)); GLCALL(glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(Sphere) * _currentScene.GetSpheres().size(),
	// _currentScene.GetSpheres().data()));
	GLCALL(glBindImageTexture(0, _colorTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);)
	GLCALL(glDispatchCompute(_width / 8, _height / 8, 1);)
	GLCALL(glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);)

	// draw the screen, (update the output basically)
	_shaderProgram.Use();
	GLCALL(glBindVertexArray(_vao);)
	GLCALL(glDrawArrays(GL_TRIANGLES, 0, 6);)
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0);)

	auto renderEndTime = std::chrono::high_resolution_clock::now();
	_lastFrameDeltaTime = renderEndTime - renderStartTime;
}

bool Renderer::PreparePipeline() {
	const std::vector<GLfloat> vertices = {
	    -1.0f,
	    1.0f,// top left
	    1.0f,
	    -1.0f,// bottom right
	    -1.0f,
	    -1.0f,// bottom left
	    1.0f,
	    -1.0f,// bottom right
	    -1.0f,
	    1.0f,// top left
	    1.0f,
	    1.0f// top right
	};

	// setup frame buffer
	GLCALL(glGenFramebuffers(1, &_fbo);)
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, _fbo);)

	OpenGLLayer::CreateTexture(_width, _height, _colorTexture);

	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorTexture, 0);)
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0);)

	GLCALL(glGenVertexArrays(1, &_vao);)
	GLCALL(glBindVertexArray(_vao);)

	GLCALL(glGenBuffers(1, &_vbo);)
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, _vbo);)
	GLCALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);)

	GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);)
	GLCALL(glEnableVertexAttribArray(0);)

	_shaderProgram = ShaderProgram("../Shaders/VertexShader1.vert", "../Shaders/FragmentShader1.frag");
	_shaderProgram.cookThatShader();
	_shaderProgram.LogInfo();
	_shaderProgram.Use();

	_computeShaderProgram = ComputeShaderProgram("../Shaders/RaytracerCompute1.comp");
	_computeShaderProgram.cookThatShader();
	_computeShaderProgram.LogInfo();
	_computeShaderProgram.Use();
	_computeShaderProgram.SetUniform2f("uImageSize", Vec4(float(_width), float(_height), 0.0f, 0.0f));
	_computeShaderProgram.SetUniform1i("uNumSpheres", _currentScene.GetSpheres().size());

	// prepare sphere data


	// prepare ssbo for sphere data
	GLCALL(glGenBuffers(1, &_SphereSSBO));
	GLCALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, _SphereSSBO));
	GLCALL(glBufferData(GL_SHADER_STORAGE_BUFFER,
	                    sizeof(Sphere) * _currentScene.GetSpheres().size(),
	                    _currentScene.GetSpheres().data(),
	                    GL_DYNAMIC_READ));
	GLCALL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, _SphereSSBO));
	GLCALL(glBufferSubData(GL_SHADER_STORAGE_BUFFER,
	                       0,
	                       sizeof(Sphere) * _currentScene.GetSpheres().size(),
	                       _currentScene.GetSpheres().data()));
	GLCALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));

	// prepare ssbo for camera data
	GLCALL(glGenBuffers(1, &_cameraSSBO));
	GLCALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, _cameraSSBO));
	GLCALL(glBufferData(GL_SHADER_STORAGE_BUFFER,
	                    sizeof(Camera),
	                    _currentScene.GetCamera().GetCameraVectors().data(),
	                    GL_DYNAMIC_READ));
	GLCALL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, _cameraSSBO));
	GLCALL(glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(Camera), _currentScene.GetCamera().GetCameraVectors().data()));
	GLCALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));

	return true;
}

void Renderer::SetCurrentScene(const Scene& scene) { _currentScene = scene; }

Color4 ComputeLighting(const RayHit& rayHit, const PointLight& light, const Vec4& viewDir) {
	const Material material = rayHit.Object()->GetMaterial();

	Color4 effColor = material.SurfaceColor() * light.GetIntensity();
	Vec4 lightVec = (light.GetPosition() - rayHit.HitPoint()).Normalize();
	Color4 ambientColor = effColor * material.Ambient();
	float angleLN = Dot(lightVec, rayHit.Normal());
	Vec4 eyeVec = (viewDir - rayHit.HitPoint()).Normalize();

	Color4 diffuse = Color4();
	if(angleLN > 0.0f) diffuse = effColor * material.Diffuse() * angleLN;

	// angle between reflection vector and eye vector
	Color4 specular = Color4();
	float angleRE = Dot(Reflect(-lightVec, rayHit.Normal()), eyeVec);
	if(angleRE >= 0.0f) specular = light.GetIntensity() * material.Specular() * powf(angleRE, material.Shininess());

	return ambientColor + diffuse + specular;
}

uint16_t Renderer::GetWidth() const { return _width; }
uint16_t Renderer::GetHeight() const { return _height; }
unsigned int Renderer::GetFrameBufferID() const { return _colorTexture; }
std::chrono::duration<float, std::milli> Renderer::GetLastFrameDeltaTime() const { return _lastFrameDeltaTime; }

void Renderer::SetImageDimensions(uint16_t width, uint16_t height) {
	_width = width;
	_height = height;
	_aspectRatio = float(_width) / float(_height);
}

}// namespace MIRT