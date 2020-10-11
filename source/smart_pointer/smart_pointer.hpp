// Copyright 2020 Roger Peralta Aranibar
#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>
#include <iostream>
/*
 * Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPointers puedan acceder al mismo recurso compartido.
 * Cuando el ˙ltimo puntero es eliminado, se elimina y libera el recurso.
 */
struct cont{
  int contador=0;
};
///
template <typename Type>
class SmartPointer {
 private:
  Type *resource_;
  cont *contador_;
 public:
/////////////////////////////////////////////////////////////
  explicit SmartPointer(Type *resource) {
	resource_=resource;
	contador_=new cont();
	contador_->contador+=1;
  }
/////////////////////////////////////////////////////////////
  SmartPointer(){
	contador_=new cont();
	contador_->contador+=1;
	resource_=nullptr;
  }
/////////////////////////////////////////////////////////////
  ~SmartPointer() {
    if(resource_){
      contador_->contador-=1;
	  if(contador_->contador==0){
	    delete resource_;
	    delete contador_;
	  }
	}
    else{
	  delete resource_;
      delete contador_;
	}
  }
/////////////////////////////////////////////////////////////
  Type &operator*() const { 
	return *resource_; 
  }
/////////////////////////////////////////////////////////////
  Type *operator->() const { 
	return resource_; 
  }
/////////////////////////////////////////////////////////////
  SmartPointer &operator=(const SmartPointer &other) { 
	if(resource_ != other.resource_){
		contador_->contador-=1;
		if(contador_->contador == 0){
			delete resource_;
			delete contador_;
		}
		resource_=other.resource_;
		contador_=other.contador_;
		contador_->contador+=1;
	}
	return *this; 
  }
/////////////////////////////////////////////////////////////////
  SmartPointer &operator=(Type *other) { 
	if(resource_){
		Detach();
	}
	contador_= new cont();
	contador_->contador+=1;
	resource_= other;
	return *this; 
  }
/////////////////////////////////////////////////////////////
  SmartPointer(const SmartPointer &other) {
	if(other.resource_){
		resource_=other.resource_;
		contador_=other.contador_;
		contador_->contador+=1;
	}
  }
/////////////////////////////////////////////////////////////////
  Type *GetPointer() const { 
	return resource_; 
  }
/////////////////////////////////////////////////////////////
  size_t GetReferenceCount() const { 
	return contador_->contador; 
  }
/////////////////////////////////////////////////////////////
  void Detach() {
	contador_->contador-=1;
	if(contador_->contador == 0){
		delete resource_;
		delete contador_;
	}
	else{
		resource_=nullptr;
		contador_=nullptr;	
	}
  }
};

#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
