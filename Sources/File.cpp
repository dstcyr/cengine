#include "File.h"
#include "Log.h"

void CFile::Release()
{
    free(m_buffer);
    m_buffer = 0;
    m_position = 0;
    m_size = 0;
}

unsigned int CFile::GetSize()
{
    return m_size;
}

bool CFile::IsEOF()
{
    return m_position >= m_size;
}

CFile::CFile() :
    m_buffer(0), m_size(0), m_position(0)
{
}

bool CFile::Exists(const std::string& filename)
{
    FILE* file;
    errno_t tFileResult = fopen_s(&file, filename.c_str(), "rb");
    if (file)
    {
        fclose(file);
        return true;
    }

    return false;
}

void CFile::Rewind()
{
    m_position = 0;
}

void CFile::Seek(unsigned int pos)
{
    if (pos > m_size)
    {
        m_position = m_size;
    }
    else if (pos < 0)
    {
        m_position = 0;
    }
    else
    {
        m_position = pos;
    }
}

void CFile::SeekEnd()
{
    Seek(m_size);
}

void CFile::SeekStart()
{
    Seek(0);
}

void CFile::Move(unsigned int pos)
{
    int newPos = m_position + pos;
    Seek(newPos);
}

void CFile::Resize(int size)
{
    if (m_buffer == nullptr)
    {
        m_buffer = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * size));
        m_size = size;
    }
    else
    {
        unsigned char* tempBuffer = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * m_size));
        CHECK(tempBuffer);
        memcpy(tempBuffer, m_buffer, m_size);
        free(m_buffer);

        m_buffer = static_cast<unsigned char*>(realloc(tempBuffer, size));
        CHECK(m_buffer);
        m_size = size;
    }
}

void CFile::WriteInt(int data)
{
    Write(&data, sizeof(int));
}

void CFile::WriteFloat(float data)
{
    Write(&data, sizeof(float));
}

void CFile::WriteByte(char data)
{
    Write(&data, sizeof(char));
}

void CFile::WriteString(const std::string str)
{
    char bufferLen = static_cast<char>(str.size());
    WriteByte(bufferLen);
    char* buffer = const_cast<char*>(str.c_str());
    Write(buffer, bufferLen);
}

void CFile::Write(void* ptr, unsigned int size)
{
    if (m_position >= m_size)
    {
        Resize(m_size + size);
    }

    CHECK(m_buffer);
    memcpy(&m_buffer[m_position], ptr, size);
    m_position += size;
}

void CFile::Load(const std::string& aFilename)
{
    FILE* file;
    m_position = 0;

    errno_t tFileResult = fopen_s(&file, aFilename.c_str(), "rb");

    CHECK(file);

    //To create the right buffer, we must get the file size first:
    fseek(file, 0, SEEK_END);
    m_size = static_cast<int>(ftell(file));
    rewind(file);

    m_buffer = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * m_size));
    CHECK(m_buffer);

    fread(m_buffer, 1, m_size, file);
    fclose(file);
}

void CFile::Save(const std::string& aFilename)
{
    FILE* file;
    fopen_s(&file, aFilename.c_str(), "wb");
    CHECK(file);
    fwrite(m_buffer, m_size, 1, file);
    fclose(file);
}

void CFile::Read(void* ptr, unsigned int size)
{
    if ((m_position + size) > m_size)
    {
        size = m_size - m_position;
    }

    memcpy(ptr, &m_buffer[m_position], size);
    m_position += size;
}

const std::string CFile::ReadString()
{
    char bufferLen = 0;
    Read(&bufferLen, sizeof(char));
    char* buffer = static_cast<char*>(malloc(bufferLen + 1));
    Read(buffer, static_cast<unsigned int>(bufferLen));

    CHECK(buffer);
    buffer[bufferLen] = '\0';
    std::string result = std::string(buffer);
    free(buffer);
    return result;
}

const int CFile::ReadInt()
{
    int readValue = 0;
    Read(&readValue, sizeof(int));
    return readValue;
}

const float CFile::ReadFloat()
{
    float readValue = 0.0f;
    Read(&readValue, sizeof(float));
    return readValue;
}

const char CFile::ReadByte()
{
    char readValue = 0;
    Read(&readValue, sizeof(char));
    return readValue;
}
