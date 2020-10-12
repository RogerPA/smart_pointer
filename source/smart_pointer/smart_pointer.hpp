// Copyright 2020 Roger Peralta Aranibar
// Hacer PullRequest Daryl Butron Cuayla

// Referencias:
// https://www.acodersjourney.com/implementing-smart-pointer-using-reference-counting/
// https://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one
// https://www.geeksforgeeks.org/smart-pointers-cpp/
// https://stackoverflow.com/questions/179105/why-shouldnt-you-use-references-to-smart-pointers
// https://es.wikipedia.org/wiki/Puntero_inteligente

#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>
//
/*
 * El smart pointer necesita de un contador de referencias
 * para esto se tiene una clase que maneje al contador de referencias
 * el incremento, decremento y como obtener el atributo contador de referencias
 */
class reference_count {
  size_t contador;

 public:
  reference_count() : contador(0) {}
  size_t ref_increment() { return ++contador; }
  size_t ref_decrement() { return --contador; }
  size_t get_ref_count() { return contador; }
};

/*
 * Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPointers puedan acceder al mismo recurso compartido.
 * Cuando el ultimo puntero es eliminado, se elimina y libera el recurso._yes
 */
template <typename Type>
class SmartPointer {
  Type *resource_;
  reference_count *r_count_;

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
  // Constructor con parametro *resource
  explicit SmartPointer(Type *resource)
      : resource_(resource), r_count_(new reference_count()) {
    r_count_->ref_increment();
  }
  // Constructor sin parametro
  SmartPointer() : resource_(nullptr), r_count_(new reference_count()) {
    r_count_->ref_increment();
  }

  /* Destructor: ~SmartPointer();
   * Uso: (implícito)
   * ------------------------------------------------------------
   * Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el último SmartPointer apuntando
   * al recurso.
   */
  // Destructor
  virtual ~SmartPointer() { delete_obj(); }
  // Metodo: Libera memoria del contador y el recurso si cumple la condicion

  /* SmartPointer operadores de "des-referencia"(dereference)
   * Uso: cout << *myPtr << endl;
   * Uso: cout << myPtr->length << endl;
   * ------------------------------------------------------------
   * Permite al SmartPointer comportarse como si fuera un puntero.
   */

  // Operador: dereferencia
  Type &
  operator*() const {
    return *resource_;
  }
  // Operador: acceso a miembro
  Type *operator->() const { return resource_; }

  /* Funciones de copia
   * Uso: SmartPointer<string> ptr=existingPointer;
   *      ptr=existingPtr;
   * ------------------------------------------------------------
   * Cambia el recurso referenciado por este SmartPointer por otro
   * SmartPointer. Si el conteo llega a cero, debe ser eliminado
   * (deallocated).
   */
  // Operador: Asignacion del Puntero Inteligente
  SmartPointer &operator=(const SmartPointer &other) {
    if (this != &other) {
      delete_obj();
      resource_ = other.GetPointer();
      r_count_ = other.GetObjCount();
      r_count_->ref_increment();
    }

    return *this;
  }

  // Operador: Asignacion del Recurso
  SmartPointer &operator=(Type *other) {
    if (resource_ != other) {
      delete_obj();
      resource_ = other;
      r_count_ = new reference_count();
      r_count_->ref_increment();
    }

    return *this;
  }

  // Constructor Copia: Toma el Puntero Inteligente en un nuevo objeto
  // Se copia other y luego se limpia de la memoria
  // El Puntero inteligente queda como unico
  SmartPointer(const SmartPointer &other) {
    this->resource_ = other.GetPointer();
    this->r_count_ = other.GetObjCount();
    r_count_->ref_increment();
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
  reference_count *GetObjCount() const { return r_count_; }
  size_t GetReferenceCount() const { return r_count_->get_ref_count(); }

  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */
  void Detach() {
    delete_obj();
    resource_ = nullptr;
    r_count_ = nullptr;
  }

  void delete_obj() {
    r_count_->ref_decrement();
    if (r_count_ && r_count_->get_ref_count() == 0) {
      delete resource_;
      delete r_count_;
    }
  }
};

#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
