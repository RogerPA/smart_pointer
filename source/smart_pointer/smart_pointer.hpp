// Copyright 2020 Roger Peralta Aranibar
#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>
#include <memory>
#include <iostream>

using namespace std;


class ReferenceCount
{
private:
  int m_RefCount{ 0 };
public:
  void Increment()
  {
    ++m_RefCount;
  }
  int Decrement()
  {
    return --m_RefCount;
  }
  int GetCount() const
  {
    return m_RefCount;
  }
};

/*
 * Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPointers puedan acceder al mismo recurso compartido.
 * Cuando el ˙ltimo puntero es eliminado, se elimina y libera el recurso.
 */
template <typename Type>
class SmartPointer {
 private:
    Type *resource;
    ReferenceCount* controlBlock{nullptr};

 public:
  
  /* Constructor: SmartPointer(Type* resource=NULL)
   * Uso: SmartPointer<string> myPtr(new string);
   *      SmartPointer<string> myPtr;*/
  explicit SmartPointer(Type* ptr = nullptr) {resource = ptr;}
 
  /* Construye un nuevo objeto SmartPointer que administra el recurso
   * asignado. Se asume que el recurso viene de una llamada a new.
   * El recurso también podría ser NULL lo que ocasionaría que el
   * recurso no administre ningún recurso.*/

  explicit SmartPointer(Type *ptr)
    :resource(ptr), controlBlock(new ReferenceCount()) {
      controlBlock->Increment();
    }
   
  /* Destructor: ~SmartPointer();
   * Uso: (implícito)*/
  
   /*Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el último SmartPointer apuntando
   * al recurso.*/
  
  virtual ~SmartPointer() {
      if(controlBlock)
      {
        int decrementCount = controlBlock->Decrement();
        cout<<"Smart_ptr destruido!"<<endl;
        if(decrementCount <= 0)
        {
          delete controlBlock;
          delete resource;

          controlBlock = nullptr;
          resource = nullptr;
        }
      }
  }

  /* SmartPointer operadores de "des-referencia"(dereference)
   * Uso: cout << *myPtr << endl;
   * Uso: cout << myPtr->length << endl;
   * ------------------------------------------------------------
   * Permite al SmartPointer comportarse como si fuera un puntero.
   */
  Type &operator*() const { return Type(0); }
  Type *operator->() const { return nullptr; }

  /* Funciones de copia
   * Uso: SmartPointer<string> ptr=existingPointer;
   *      ptr=existingPtr;
   * ------------------------------------------------------------
   * Cambia el recurso referenciado por este SmartPointer por otro
   * SmartPointer. Si el conteo llega a cero, debe ser eliminado
   * (deallocated).
   */
  SmartPointer &operator=(const SmartPointer<Type> &other) 
  {
    if(this != &other)
    {
      if(controlBlock and controlBlock->Decrement() == 0)
      {
        delete controlBlock;
        delete resource;
      }
      resource = other.resource;
      controlBlock = other.controlBlock;
      controlBlock->Increment();
    }
  }

  SmartPointer &operator=(Type *other) { return *this; }

  SmartPointer(const SmartPointer<Type> &other) 
    :resource{ other.resource },
     controlBlock{ other.controlBlock}
  {
    controlBlock->Increment();
    cout<<"Smart_ptr copiado!"<<controlBlock->GetCount()<<endl;

  }


  /* Helper Function: Obtener recurso.
   * Uso: Type* p=GetPointer();
   * ------------------------------------------------------------
   * Retorna una variable puntero al recurso administrado.
   */
  Type *GetPointer() const { return nullptr; }

  /* Helper Function: Obtiene conteo
   * Uso: if (ptr.GetReferenceCount()==1) // Única referencia
   * ------------------------------------------------------------
   * Retorna el número de referencias apuntando al recurso.
   */
  size_t GetReferenceCount() const { return 0; }

  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */
  void Detach() {
    if(resource and --(*controlBlock) == 0)
    {
      delete resource;
      delete controlBlock;
    }
    resource = nullptr;
    controlBlock = nullptr;
  }
};

#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
