// Copyright 2020 Roger Peralta Aranibar
#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>

class ReferenceCounter {
 private:
  int count;

 public:
  ReferenceCounter() : count(0) {}
  virtual ~ReferenceCounter() {}

  void AddRef() { ++count; }

  int GetCount() const { return count; }

  void Release() { --count; }
};

/*
 * Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPointers puedan acceder al mismo recurso compartido.
 * Cuando el ultimo puntero es eliminado, se elimina y libera el recurso.
 */
template <typename Type>
class SmartPointer {
 private:
  Type *resource_;
  ReferenceCounter *ref_counter;

 public:
  /* Constructor: SmartPointer(Type* resource=NULL)
   * Uso: SmartPointer<string> myPtr(new string);
   *      SmartPointer<string> myPtr;
   * ------------------------------------------------------------
   * Construye un nuevo objeto SmartPointer que administra el recurso
   * asignado. Se asume que el recurso viene de una llamada a new.
   * El recurso también podría ser NULL lo que ocasionaría que el
   * recurso no administre ningún recurso.
   */
  explicit SmartPointer(Type *resource) : resource_(resource) {
    this->ref_counter = new ReferenceCounter();
    this->ref_counter->AddRef();
  }

  SmartPointer() : resource_(nullptr) {
    ref_counter = new ReferenceCounter();
    ref_counter->AddRef();
  }

  /* Destructor: ~SmartPointer();
   * Uso: (implícito)
   * ------------------------------------------------------------
   * Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el último SmartPointer apuntando
   * al recurso.
   */
  ~SmartPointer() {
    this->ref_counter->Release();
    if (ref_counter->GetCount() == 0) {
      delete this->resource_;
      delete this->ref_counter;
    }
  }

  /* SmartPointer operadores de "des-referencia"(dereference)
   * Uso: cout << *myPtr << endl;
   * Uso: cout << myPtr->length << endl;
   * ------------------------------------------------------------
   * Permite al SmartPointer comportarse como si fuera un puntero.
   */
  Type &operator*() const { return *resource_; }
  Type *operator->() const { return resource_; }

  /* Funciones de copia
   * Uso: SmartPointer<string> ptr=existingPointer;
   *      ptr=existingPtr;
   * ------------------------------------------------------------
   * Cambia el recurso referenciado por este SmartPointer por otro
   * SmartPointer. Si el conteo llega a cero, debe ser eliminado
   * (deallocated).
   */
  SmartPointer &operator=(const SmartPointer &other) {
    if (this != &other) {
      ref_counter->Release();
      if (ref_counter->GetCount() == 0) {
        delete resource_;
        delete ref_counter;
      }

      resource_ = other.resource_;
      ref_counter = other.ref_counter;
      ref_counter->AddRef();
    }

    return *this;
  }

  SmartPointer &operator=(Type *other) {
    if (resource_ != other) {
      ref_counter->Release();
      if (ref_counter->GetCount() == 0) {
        delete resource_;
        delete ref_counter;
      }

      resource_ = other;
      ref_counter = new ReferenceCounter();
      ref_counter->AddRef();
    }
    return *this;
  }

  SmartPointer(const SmartPointer &other) {
    this->resource_ = other.resource_;
    this->ref_counter = other.ref_counter;
    this->ref_counter->AddRef();
  }

  /* Helper Function: Obtener recurso.
   * Uso: Type* p=GetPointer();
   * ------------------------------------------------------------
   * Retorna una variable puntero al recurso administrado.
   */
  Type *GetPointer() const { return resource_; }

  /* Helper Function: Obtiene conteo
   * Uso: if (ptr.GetReferenceCount()==1) // Única referencia
   * ------------------------------------------------------------
   * Retorna el número de referencias apuntando al recurso.
   */
  size_t GetReferenceCount() const { return ref_counter->GetCount(); }

  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */
  void Detach() {
    if (resource_ != nullptr) {
      ref_counter->Release();
      if (ref_counter->GetCount() == 0) {
        delete resource_;
        delete ref_counter;
      }

      resource_ = nullptr;
      ref_counter = new ReferenceCounter();
      ref_counter->AddRef();
    }
  }
};

#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
