#pragma once
#include <string>

class CFile
{
public:
    CFile();

    static bool Exists(const std::string& filename);
    void Rewind();
    void Seek(unsigned int pos);
    void SeekEnd();
    void SeekStart();
    void Move(unsigned int pos);
    void Resize(int size);
    bool IsEOF();
    void WriteInt(int data);
    void WriteFloat(float data);
    void WriteByte(char data);
    void WriteString(const std::string str);
    void Write(void* ptr, unsigned int size);
    const int ReadInt();
    const float ReadFloat();
    const char ReadByte();
    const std::string ReadString();
    void Read(void* ptr, unsigned int size);
    void Load(const std::string& filename);
    void Save(const std::string& filename);
    void Release();
    unsigned int GetSize();

private:
    unsigned char* m_buffer;
    unsigned int m_size;
    unsigned int m_position;
};