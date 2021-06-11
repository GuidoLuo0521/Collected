#pragma once

template<class T> class Singleton 
{
public:
  Singleton():instance_(NULL)
  {
  }

  virtual ~Singleton() 
  {
  }

  static T* setInstance(T* p)
  {
	  T* t = getInstance();
	  singleton_->instance_ = p;
	  return t;
  }


  static T* getInstance() 
  {
	  if (singleton_ == NULL)
	  {
		  singleton_ = new Singleton<T>();
	  }

    return  singleton_->instance_;
  }
  static void cleanup()
  {
	  singleton_->cleanup_i();
  }
private:
  void cleanup_i()
  {
	  delete this;
  }

private:
  static Singleton<T>*	singleton_;
  T*			instance_;
};

template<class T> Singleton<T> *Singleton<T>::singleton_ = 0;

