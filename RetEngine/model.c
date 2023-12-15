#include "include.h"
#include "model.h"
#include "shader.h"

void drawModel(Model model, unsigned int shader, unsigned int VAO) {
	useShader(shader);
	glBindVertexArray(VAO);

	mat4 modelMatrix = GLM_MAT4_IDENTITY_INIT;
	glm_translate(modelMatrix, model.position);
	glm_rotate(modelMatrix, glm_rad(model.rotationAngle), model.rotationAxis);
	glm_scale(modelMatrix, model.scale);
	setMat4(shader, "model", modelMatrix);

	glDrawArrays(GL_TRIANGLES, 0, model.vertexCount);
}
