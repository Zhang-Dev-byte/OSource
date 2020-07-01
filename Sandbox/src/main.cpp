#include <OSource.h>

class Sandbox : public OSource::Application{
public:
	virtual void Run() override{
	}
	virtual void Render() override{
		unsigned int VAO, VBO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		float vertices[3*3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    	glEnableVertexAttribArray(0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0); 

		glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	virtual void HandleInput(OSource::Input& input) override{
	}
};

OSource::Application* OSource::CreateApplication(){
	return new Sandbox();
}