//
// Created by 陈奕锟 on 2022/10/3.
//

#ifndef OPENGL_BASICRENDERERPROJECT_INDEXBUFFER_H
#define OPENGL_BASICRENDERERPROJECT_INDEXBUFFER_H

#endif //OPENGL_BASICRENDERERPROJECT_INDEXBUFFER_H

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};
