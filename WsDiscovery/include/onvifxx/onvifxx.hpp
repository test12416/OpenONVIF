#ifndef ONVIFXX_H
#define ONVIFXX_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#define UNUSED(x) (void)x

struct soap;

#if __GNUC_MINOR__ < 6
    #define noexcept throw()

    const class {                       // this is a const object...
    public:
        template<class T>               // convertible to any type
        operator T*() const             // of null non-member
        { return 0; }                   // pointer...
        template<class C, class T>      // or any type of null
        operator T C::*() const         // member pointer...
        { return 0; }
    private:
        void operator&() const;         // whose address can't be taken
    } nullptr = {};                     // and whose name is nullptr
#endif

namespace onvifxx {

class Exception : public std::exception
{
public:
    Exception();
    Exception(const char * msg);
    virtual ~Exception() throw();
    virtual const char * what() const throw();

protected:
    std::string & message();

private:
    std::string msg_;

};

class SoapException : public Exception
{
public:
    SoapException(soap * s);

    int code() const;

private:
    int code_;
};

class UnixException : public Exception
{
public:
    UnixException(int code = 0);

    int code() const;

private:
    int code_;
};

template<class T>
struct Proxy : T
{
    virtual ~Proxy()
    {
    }
};

template<class T>
struct Service
{
    virtual ~Service() {}

    virtual soap* getSoap() = 0;

    virtual int bind(T * obj, int port = 0) = 0;
    virtual	int accept() = 0;
    virtual	int serve() = 0;
    virtual	void destroy() = 0;
};

template<class T, class I>
struct BaseService : Service<T>, I
{
    T * p;

    BaseService()
    {
        p = nullptr;
    }

    virtual int bind(T * obj, int port)
    {
        p = obj;
        if (port == 0)
            port = 80;
        return I::bind(nullptr, port, 100);
    }

    virtual	int serve()
    {
        return I::serve();
    }

    virtual	int accept()
    {
        return I::accept();
    }

    virtual	void destroy()
    {
        I::destroy();
    }
};

//template<class T>
//class Pimpl
//{
//public:
//    Pimpl() : p_(new T) { }
//    T * impl() { return p_.get(); }
//private:
//    std::shared_ptr<T> p_;
//};

} // namespace onvifxx

#endif //ONVIFXX_H
