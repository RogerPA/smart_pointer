// Copyright 2020 Roger Peralta Aranibar
#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>

/*
SMART POINTER:
- Cada smart pointer guarda una referencia a un objeto RefCounter que se encarga de contar las 
  referencias de otros smart pointers hacia un objeto.
- Los smart pointers referencian al objeto a traves del objeto RefCounter y no directamente, 
  esto para solo tener que conectar un smart pointer a otro RefCounter y ya no tener que hacer 
  lo mismo con resource_.
- El modelo de smart pointer que utilicé:

        smart_p1
                 \
        smart_p2 ¬> RefCounter(3)->object
                 /
        smart_p3

  RefCounter contiene:
    - resource_ -> El enlace o referencia al recurso.
    - counter -> Un contador de referencias.
    - Un constructor que inicia el contador = 1 ya que se puede iniciar solo mediante un smart 
      pointer y eso significa desde ya un enlace y tambien referencia resource_ al recurso dado.
    - Un destructor que elimina el recurso asignado.
    - change_obj -> Referencia a otro recurso dado.
    - sub_ptr -> Disminuye el contador en 1.
    - add_ptr -> Aumenta el contador en 1.
*/

template <typename Type>
class SmartPointer {
 private:
  struct RefCounter {
    Type *resource_;
    size_t counter;
    RefCounter(Type *resource) : resource_(resource) { counter = size_t(1); }
    ~RefCounter() {
      delete resource_;
      resource_ = nullptr;
    }
    void change_obj(Type *resource) { resource_ = resource; }
    void sub_ptr() { --counter; };
    void add_ptr() { ++counter; }
  } * manager;

  //"Desenlaza" (ya que es una funcion que se usa internamente
  // para el smart pointer no cambio el enlace, sino que solo descuento el
  // contador de su RefCounter en 1) un smart pointer de su RefCounter actual y
  // si era el ultimo smart pointer de ese RefCounter, entonces se elimina el
  // recurso y su RefCounter.

  void remove_smartptr() {
    manager->sub_ptr();
    if (!GetReferenceCount()) {
      delete manager;
      manager = nullptr;
    }
  }

  // Enlaza el smart pointer al RefCounter del smart pointer "other" e
  // incrementa el contador del mismo en 1 por el enlace nuevo.

  void move_smartptr(const SmartPointer &other) {
    manager = other.manager;
    manager->add_ptr();
  }

 public:
  explicit SmartPointer(Type *resource) { manager = new RefCounter(resource); }

  ~SmartPointer() { remove_smartptr(); }

  Type &operator*() const { return *GetPointer(); }
  Type *operator->() const { return GetPointer(); }

  SmartPointer &operator=(const SmartPointer &other) { 
    if (manager != other.manager) {// Si ambos smart pointers ya estan referenciando al mismo RefCounter no se deberia hacer algo.
      remove_smartptr();
      move_smartptr(other);
    }
    return *this; 
  }
  SmartPointer &operator=(Type *other) { 
    if (GetPointer() != other) {// Si resource_ de el RefCounter actual y "other" coinciden es porque el smart pointer ya referenciaba a ese recurso por medio del RefCounter
      Detach();
      manager->change_obj(other);
    }
    return *this; 
  }
  SmartPointer(const SmartPointer &other) { 
    move_smartptr(other);
  }

  Type *GetPointer() const { return manager->resource_; }

  size_t GetReferenceCount() const { return manager->counter; }

  // Literalmente si la referencia al recurso es un puntero null no es necesario
  // un detach porque eso es lo que hace: ("Seria hacer un detach por gusto")
  // 1. Remueve el smart pointer de su RefCounter.
  // 2. Le asigna su propio RefCounter con un resource_ nulo.
  void Detach() {
    if (GetPointer()) {
      remove_smartptr();
      manager = new RefCounter(nullptr);
    }
  }
};

#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_