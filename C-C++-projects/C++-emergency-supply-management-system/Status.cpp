#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <string.h>
#include "Utils.h"
#include "Status.h"

using namespace std;

Status::Status(const char* status)
{
    // Checking for argument.
    if (status)
    {
        // Assigning argument into status.
        ut.alocpy(m_status, status);
        // Setting code.
        m_code = 0;
    }
    else
    {
        // Initializing both members without arguments.
        m_status = nullptr;
        m_code = 0;
    }
}

Status& Status::clear()
{
    // Safely deallocating memory from the description.
    if (m_status)
    {
        delete[] m_status;
        m_status = nullptr;
    }
    // Setting code to zero.
    m_code = 0;

    return *this;
}

Status::Status(const Status& st)
{
    m_code = 0;

    if (st.m_status)
    {
        ut.alocpy(m_status, st.m_status);
        m_code = st.m_code;
    }
}

Status& Status::operator=(const Status& st)
{
    // Checking for self-assignment.
    if (this != &st)
    {
        clear();

        if (st.m_status)
        {
            ut.alocpy(m_status, st.m_status);
            m_code = st.m_code;
        }
    }

    return *this;
}

Status& Status::operator=(const char* status)
{
    delete[] m_status;
    m_status = nullptr;

    // Checking for argument.
    if (status)
    {
        ut.alocpy(m_status, status);
    }

    return *this;
}

Status& Status::operator=(int code)
{
    // Assigning code.
    m_code = code;

    return *this;
}

Status::~Status()
{
    delete[] m_status;
    m_status = nullptr;
}

Status::operator int() const
{
    return m_code;
}

Status::operator const char* () const
{
    return m_status;
}

Status::operator bool() const
{
    // Validating null description.
    return m_status == nullptr;
}

std::ostream& operator<<(std::ostream& ostr, const Status& status)
{
    // Checking if status is in a bad state (operator).
    if (!status)
    {
        if (status.m_code != 0)
        {
            ostr << "ERR#" << status.m_code << ": ";

        }
        if (status.m_status)
        {
            ostr << status.m_status;
        }
    }

    return ostr;
}