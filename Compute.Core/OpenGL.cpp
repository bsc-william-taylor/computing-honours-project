
#include "OpenGL.h"
#include "gl/GLU.h"
#include "gl/gl.h"

void glClearColor(v8::FunctionArgs args)
{
    if (args.Length() == 4)
    {
        auto r = args[0].As<v8::Number>()->Value();
        auto g = args[1].As<v8::Number>()->Value();
        auto b = args[2].As<v8::Number>()->Value();
        auto a = args[3].As<v8::Number>()->Value();

        glClearColor(r, g, b, a);
    }
}

void glClear(v8::FunctionArgs args)
{
    if (args.Length() == 1)
    {
        glClear(args[0]->NumberValue());
    }
}

void glBegin(v8::FunctionArgs args)
{
    if (args.Length() == 1)
    {
        glBegin(static_cast<GLenum>(args[0]->NumberValue()));
    }
}

void glColor3(v8::FunctionArgs args)
{
    if (args.Length() == 3)
    {
        auto r = args[0].As<v8::Number>()->Value();
        auto g = args[1].As<v8::Number>()->Value();
        auto b = args[2].As<v8::Number>()->Value();

        glColor3f(r, g, b);
    }
}

void glVertex2(v8::FunctionArgs args)
{
    if (args.Length() == 2)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();

        glVertex2f(x, y);
    }
}

void glVertex3(v8::FunctionArgs args)
{
    if (args.Length() == 3)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();
        auto z = args[2].As<v8::Number>()->Value();

        glVertex3f(x, y, z);
    }
}

void glLoadIdentity(v8::FunctionArgs args)
{
    ::glLoadIdentity();
}

void glMatrixMode(v8::FunctionArgs args)
{
    if (args.Length() == 1)
    {
        ::glMatrixMode(args[0].As<v8::Number>()->Value());
    }
}

void glTranslate(v8::FunctionArgs args)
{
    if (args.Length() == 3)
    {
        auto x = args[0].As<v8::Number>()->Value();
        auto y = args[1].As<v8::Number>()->Value();
        auto z = args[2].As<v8::Number>()->Value();

        glTranslatef(x, y, z);
    }
}

void glRotate(v8::FunctionArgs args)
{
    if (args.Length() == 4)
    {
        auto r = args[0].As<v8::Number>()->Value();
        auto x = args[1].As<v8::Number>()->Value();
        auto y = args[2].As<v8::Number>()->Value();
        auto z = args[3].As<v8::Number>()->Value();

        glRotatef(r, x, y, z);
    }
}

void glPerspective(v8::FunctionArgs args)
{
    if (args.Length() == 4)
    {
        auto fov = args[0].As<v8::Number>()->Value();
        auto aspect = args[1].As<v8::Number>()->Value();
        auto min = args[2].As<v8::Number>()->Value();
        auto max = args[3].As<v8::Number>()->Value();

        gluPerspective(fov, aspect, min, max);
    }
}

void glEnd(v8::FunctionArgs args)
{
    glEnd();
}

void glEnable(v8::FunctionArgs args)
{
    if (args.Length() == 1)
    {
        glEnable(args[0].As<v8::Integer>()->Value());
    }
}

void glGetError(v8::FunctionArgs args)
{
    args.GetReturnValue().Set(glGetError());
}

void glGetResetStatus(v8::FunctionArgs args)
{
    if(GLEW_VERSION_4_5)
    {
        args.GetReturnValue().Set(glGetGraphicsResetStatus());
    }
    else
    {
        v8::Throw("Error calling GL4.5 method glGetGraphicsResetStatus");
    }
}

void glGetInterger(v8::FunctionArgs args)
{
    auto param = v8::GetNumber(args[0]);
    auto array = v8::GetArray(args[1]);
    auto length = array->Length();
  
    std::vector<int> values(length);
    glGetIntegerv(param, values.data());

    for(auto i = 0; i < length; i++)
    {
        array->Set(i, v8::NewNumber(values[i]));
    }
}

void glFlush(v8::FunctionArgs args)
{
    glFlush();
}

void glFinish(v8::FunctionArgs args)
{
    glFinish();
}

void glGenerateBuffers(v8::FunctionArgs args)
{
    auto size = GetNumber(args[0]);
    auto array = args[1].As<v8::Uint32Array>();
    auto data = array->Buffer()->GetContents().Data();
    glGenBuffers(size, static_cast<GLuint *>(data));
}

void glDelBuffers(v8::FunctionArgs args)
{
    auto size = GetNumber(args[0]);
    auto array = args[1].As<v8::Uint32Array>();
    auto data = array->Buffer()->GetContents().Data();
    glDeleteBuffers(size, static_cast<GLuint *>(data));
}

void glBindBuffers(v8::FunctionArgs args)
{
    auto target = GetNumber(args[0]);
    auto buffer = GetNumber(args[1]);

    glBindBuffer(target, buffer);
}

void glSendBufferData(v8::FunctionArgs args)
{
    auto target = GetNumber(args[0]);
    auto size = GetNumber(args[1]);
    auto array = args[2].As<v8::Float32Array>();
    auto usage = GetNumber(args[3]);
    auto data = array->Buffer()->GetContents().Data();
    glBufferData(target, size, data, usage);
}

void glEnableAttribArray(v8::FunctionArgs args)
{
    auto index = GetNumber(args[0]);
    glEnableVertexAttribArray(index);
}

void glDisableAttribArray(v8::FunctionArgs args)
{
    auto index = GetNumber(args[0]);
    glDisableVertexAttribArray(index);
}

void glSetVertexAttribPoint(v8::FunctionArgs args)
{
    auto bufferID = GetNumber(args[0]);
    auto size = GetNumber(args[1]);
    auto type = GetNumber(args[2]);
    auto normal = GetNumber(args[3]);
    auto stride = GetNumber(args[4]);

    glVertexAttribPointer(bufferID, size, type, normal, stride, nullptr);
}

void createProgram(v8::FunctionArgs args)
{
    args.GetReturnValue().Set(glCreateProgram());
}

void attachShader(v8::FunctionArgs args)
{
    auto program = GetNumber(args[0]);
    auto shader = GetNumber(args[1]);
    glAttachShader(program, shader);
}

void linkProgram(v8::FunctionArgs args)
{
    auto program = GetNumber(args[0]);
    glLinkProgram(program);
}

void useProgram(v8::FunctionArgs args)
{
    auto program = GetNumber(args[0]);
    glUseProgram(program);
}

void createShader(v8::FunctionArgs args)
{
    auto type = GetNumber(args[0]);
    args.GetReturnValue().Set(glCreateShader(type));
}

void shaderSource(v8::FunctionArgs args)
{
    auto shader = GetNumber(args[0]);
    auto count = GetNumber(args[1]);
    auto source = GetString(args[2]);
    auto sourceArray = new char*[1];

    sourceArray[0] = (char*)source.c_str();
    glShaderSource(shader, 1, sourceArray, nullptr);
    delete[] sourceArray;
}

void compileShader(v8::FunctionArgs args)
{
    auto shader = GetNumber(args[0]);
    glCompileShader(shader);
}

void deleteShader(v8::FunctionArgs args)
{
    auto shader = GetNumber(args[0]);
    glDeleteShader(shader);
}

void getShaderInfoLog(v8::FunctionArgs args)
{
    auto shader = GetNumber(args[0]);
    auto bufsz = GetNumber(args[1]);
    auto len = GetNumber(args[2]);
    auto arr = GetArray(args[3]);

    auto buffer = new char[bufsz];
    glGetShaderInfoLog(shader, bufsz, (int*)&len, buffer);
    arr->Set(0, v8::NewString(buffer));
    delete[] buffer;
}

void getShaderiv(v8::FunctionArgs args)
{
    auto shader = GetNumber(args[0]);
    auto pname = GetNumber(args[1]);
    auto array = GetArray(args[2]);

    std::vector<int> result(array->Length());
    glGetShaderiv(shader, pname, result.data());    
    for(auto i = 0; i < array->Length(); i++)
    {
       array->Set(i, v8::NewNumber(result[i]));
    }
}

void glDraw(v8::FunctionArgs args)
{
    auto mode = GetNumber(args[0]);
    auto first = GetNumber(args[1]);
    auto count = GetNumber(args[2]);
    glDrawArrays(mode, first, count);
}

void genVertexArray(v8::FunctionArgs args)
{
    auto count = v8::GetNumber(args[0]);
    auto array = v8::GetArray(args[1]);
    
    std::vector<GLuint> ids(count);
    glGenVertexArrays(count, ids.data());
    for(auto i = 0; i < count; i++)
    {
        array->Set(i, v8::NewNumber(ids[i]));
    }
}

void bindVertexArray(v8::FunctionArgs args)
{
    auto num = v8::GetNumber(args[0]);
    glBindVertexArray(num);
}

void compute::registerOpenGL(v8::Exports exports)
{
    // Command Execution
    AttachFunction(exports, "glGetError", glGetError);
    AttachFunction(exports, "glGetGraphicsResetStatus", glGetResetStatus);
    AttachFunction(exports, "glGetIntergerv", glGetInterger);
    AttachFunction(exports, "glFlush", glFlush);
    AttachFunction(exports, "glFinish", glFinish);

    // Buffer Objects
    AttachFunction(exports, "glGenBuffers", glGenerateBuffers);
    AttachFunction(exports, "glBindBuffer", glBindBuffers);
    AttachFunction(exports, "glDeleteBuffers", glDelBuffers);
    AttachFunction(exports, "glBufferData", glSendBufferData);

    AttachFunction(exports, "glVertexAttribPointer", glSetVertexAttribPoint);
    AttachFunction(exports, "glEnableVertexAttribArray", glEnableAttribArray);
    AttachFunction(exports, "glDisableVertexAttribArray", glDisableAttribArray);

    // VAO
    AttachFunction(exports, "glGenVertexArray", genVertexArray);
    AttachFunction(exports, "glBindVertexArray", bindVertexArray);

    // Shader objects
    AttachFunction(exports, "glCreateShader", createShader);
    AttachFunction(exports, "glShaderSource", shaderSource);
    AttachFunction(exports, "glCompileShader", compileShader);
    AttachFunction(exports, "glDeleteShader", deleteShader);
    AttachFunction(exports, "glCreateProgram", createProgram);
    AttachFunction(exports, "glAttachShader", attachShader);
    AttachFunction(exports, "glLinkProgram", linkProgram);
    AttachFunction(exports, "glUseProgram", useProgram);
    AttachFunction(exports, "glGetShaderiv", getShaderiv);
    AttachFunction(exports, "glGetShaderInfoLog", getShaderInfoLog);

    // Drawing functions
    AttachFunction(exports, "glDrawArrays", glDraw);
    // Deprecated Functions
    AttachFunction(exports, "gluPerspective", glPerspective);
    AttachFunction(exports, "glEnable", glEnable);
    AttachFunction(exports, "glMatrixMode", glMatrixMode);
    AttachFunction(exports, "glLoadIdentity", glLoadIdentity);
    AttachFunction(exports, "glTranslatef", glTranslate);
    AttachFunction(exports, "glRotatef", glRotate);
    AttachFunction(exports, "glClearColor", glClearColor);
    AttachFunction(exports, "glVertex3f", glVertex3);
    AttachFunction(exports, "glVertex2f", glVertex2);
    AttachFunction(exports, "glColor3f", glColor3);
    AttachFunction(exports, "glClear", glClear);
    AttachFunction(exports, "glBegin", glBegin);
    AttachFunction(exports, "glEnd", glEnd);
}