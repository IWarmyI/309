#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// store list of vertices
	std::vector<vector3> vertices;
	GLfloat angle = 0;
	GLfloat delta =2.0 * PI / a_nSubdivisions;

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// give circle half height
		vector3 temp = vector3(cos(angle) * a_fRadius, sin(angle) * a_fRadius, a_fHeight / 2.0f);
		angle += delta;
		vertices.push_back(temp);
	}

	//center point
	vector3 origin = vector3(0.0f, 0.0f, a_fHeight / 2.0f);

	// create cone tip
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(origin, vertices[i], vertices[(i + 1) % a_nSubdivisions]);
	}

	origin = vector3(0.0f, 0.0f, -a_fHeight / 2.0f);

	// connect to circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(origin, vertices[(i + 1) % a_nSubdivisions], vertices[i]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// store list of vertices
	std::vector<vector3> vertices;
	GLfloat angle = 0;
	GLfloat delta = 2.0 * PI / a_nSubdivisions;

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		// give circle half height
		vector3 temp = vector3(cos(angle) * a_fRadius, sin(angle) * a_fRadius, 0.0f);
		angle += delta;
		vertices.push_back(temp);
	}

	// store top vertices
	std::vector<vector3> topVertices;
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		topVertices.push_back(vertices[i] + vector3(0.0f, 0.0f, -a_fHeight / 2.0f));
	}

	// store bottom vertices
	std::vector<vector3> bottomVertices;
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		bottomVertices.push_back(vertices[i] + vector3(0.0f, 0.0f, a_fHeight / 2.0f));
	}

	//center point
	vector3 origin = vector3(0.0f, 0.0f, -a_fHeight / 2.0f);

	// create top/bottom circles
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(origin, topVertices[(i + 1) % a_nSubdivisions], topVertices[i]);
	}

	origin = vector3(0.0f, 0.0f, a_fHeight / 2.0f);

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(origin, bottomVertices[i], bottomVertices[(i + 1) % a_nSubdivisions]);
	}

	// connect top and bottom circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(topVertices[i], topVertices[(i + 1) % a_nSubdivisions], bottomVertices[i], bottomVertices[(i + 1) % a_nSubdivisions]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// store list of inside circle vertices
	std::vector<vector3> insideVertices;
	GLfloat angle = 0;
	GLfloat delta = 2.0 * PI / a_nSubdivisions;
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(angle) * a_fInnerRadius, sin(angle) * a_fInnerRadius, 0.0f);
		angle += delta;
		insideVertices.push_back(temp);
	}

	// outside circle verticies
	std::vector<vector3> outsideVertices;
	angle = 0;
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(angle) * a_fOuterRadius, sin(angle) * a_fOuterRadius, 0.0f);
		angle += delta;
		outsideVertices.push_back(temp);
	}

	// inside top circle vertices
	std::vector<vector3> insideTopVertices;
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		insideTopVertices.push_back(insideVertices[i] + vector3(0.0f, 0.0f, -a_fHeight / 2.0f));
	}

	// inside bottom vertices
	std::vector<vector3> insideBottomVertices;
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		insideBottomVertices.push_back(insideVertices[i] + vector3(0.0f, 0.0f, a_fHeight / 2.0f));
	}

	// outside top circle vertices
	std::vector<vector3> outsideTopVertices;
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		outsideTopVertices.push_back(outsideVertices[i] + vector3(0.0f, 0.0f, -a_fHeight / 2.0f));
	}

	// outside bottom circle vertices
	std::vector<vector3> outsideBottomVertices;
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		outsideBottomVertices.push_back(outsideVertices[i] + vector3(0.0f, 0.0f, a_fHeight / 2.0f));
	}

	// connect top/bottom circles

	// outside/inside top circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(insideTopVertices[i], insideTopVertices[(i + 1) % a_nSubdivisions],
			outsideTopVertices[i], outsideTopVertices[(i + 1) % a_nSubdivisions]);
	}

	// outside/inside bottom circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(outsideBottomVertices[i], outsideBottomVertices[(i + 1) % a_nSubdivisions],
			insideBottomVertices[i], insideBottomVertices[(i + 1) % a_nSubdivisions]);
	}

	// top/bottom inside circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(insideBottomVertices[i], insideBottomVertices[(i + 1) % a_nSubdivisions],
			insideTopVertices[i], insideTopVertices[(i + 1) % a_nSubdivisions]);
	}

	// top/bottom outside circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(outsideTopVertices[i], outsideTopVertices[(i + 1) % a_nSubdivisions],
			outsideBottomVertices[i], outsideBottomVertices[(i + 1) % a_nSubdivisions]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	// store list of inside circle vertices
	std::vector<vector3> vertices;
	GLfloat angle = 0;
	GLfloat delta = 2.0 * PI / a_nSubdivisionsA;

	// calculate radius of circle
	float circleRadius = (a_fOuterRadius - a_fInnerRadius) / 2;


	// save vertices of default circle
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		vector3 temp = vector3(cos(angle) * circleRadius, sin(angle) * circleRadius, 0.0f);
		angle += delta;
		vertices.push_back(temp);
	}

	// rotate and translate circle from origin
	for (int i = 0; i < a_nSubdivisionsB; i++)
	{
		matrix4 m4Transform = glm::rotate(IDENTITY_M4, delta * i,
			vector3(0.0f, 1.0f, 0.0f)) * glm::translate(vector3(a_fInnerRadius * 2.0f, 0.0f, 0.0f));

		// create temp list of rotated/translated vertices
		std::vector<vector3> temp;
		for (int j = 0; j < a_nSubdivisionsA; j++)
		{
			temp.push_back(m4Transform * vector4(vertices[j], 1.0f));
		}

		// connect circles with quads
		matrix4 futureMatrix = glm::rotate(IDENTITY_M4, delta * (i + 1),
			vector3(0.0f, 1.0f, 0.0f)) * glm::translate(vector3(a_fInnerRadius * 2.0f, 0.0f, 0.0f));
		for (int j = 0; j < a_nSubdivisionsA; j++)
		{
			AddQuad((futureMatrix * vector4(vertices[j], 1.0f)),
				(futureMatrix * vector4(vertices[(j + 1) % a_nSubdivisionsA], 1.0f)),
				temp[j], temp[(j + 1) % a_nSubdivisionsA]);
		}
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	// store list of vertices
	std::vector<vector3> vertices;
	
	
	int circleSubdivision = 20;
	GLfloat angle = 0;
	GLfloat circleDelta = 2.0 * PI / circleSubdivision;
	GLfloat sphereDelta = 2.0 * PI / a_nSubdivisions;

	// get vertices of regular circle
	for (int i = 0; i < circleSubdivision; i++)
	{
		vector3 temp = vector3(cos(angle) * a_fRadius, sin(angle) * a_fRadius, 0.0f);
		angle += circleDelta;
		vertices.push_back(temp);
	}

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		matrix4 m4Transform = glm::rotate(IDENTITY_M4, sphereDelta * i, vector3(1.0f, 0.0f, 0.0f));

		// temp list to copy original circle to number of circle subdivisions
		std::vector<vector3> temp;
		for (int j = 0; j < circleSubdivision; j++)
		{
			temp.push_back(m4Transform * vector4(vertices[j], 1.0f));
		}

		// connect circle subdivisions
		matrix4 futureTransform = glm::rotate(IDENTITY_M4, sphereDelta * (i + 1), vector3(1.0f, 0.0f, 0.0f));
		for (int j = 0; j < circleSubdivision / 2; j++)
		{
			AddQuad(temp[j], temp[(j + 1) % circleSubdivision],
				futureTransform * vector4(vertices[j], 1.0f),
				futureTransform * vector4(vertices[(j + 1) % circleSubdivision], 1.0f));
		}
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}