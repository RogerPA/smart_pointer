#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>
#include <map>
#include<iostream>

using namespace std;
/*Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPointers puedan acceder al mismo recurso compartido.
 * Cuando el ˙ltimo puntero es eliminado, se elimina y libera el recurso.
 */
template <typename Type>
class SmartPointer {
 private:
  Type *resource_;
  static map<Type *,int> cant_ref;

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
  explicit SmartPointer(Type *resource) :resource_(resource) {
    if(this->resource_ != nullptr)cant_ref[resource]++;
  }
  SmartPointer(){};
  /* Destructor: ~SmartPointer();
   * Uso: (implícito)
   * ------------------------------------------------------------
   * Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el último SmartPointer apuntando
   * al recurso.
   */
  ~SmartPointer() {
    if(this->resource_!=nullptr)Detach();
  }

  /* SmartPointer operadores de "des-referencia"(dereference)
   * Uso: cout << *myPtr << endl;
   * Uso: cout << myPtr->length << endl;
   * ------------------------------------------------------------
   * Permite al SmartPointer comportarse como si fuera un puntero.
   */
  Type &operator*() const { return *this->resource_; }
  Type *operator->() const { return this->resource_; }

  /* Funciones de copia
   * Uso: SmartPointer<string> ptr=existingPointer;
   *      ptr=existingPtr;
   * ------------------------------------------------------------
   * Cambia el recurso referenciado por este SmartPointer por otro
   * SmartPointer. Si el conteo llega a cero, debe ser eliminado
   * (deallocated).
   */
  SmartPointer &operator=(const SmartPointer &other) {
    if(this->resource_!=other.resource_){
      if(other.resource_!=nullptr)cant_ref[other.resource_]++; 
      if(this->resource_!=nullptr )Detach();
      
      this->resource_ = other.resource_;
    }
    return *this;
  }
  SmartPointer &operator=(Type *other) {
    if(other!=nullptr)cant_ref[other]++;
    if(this->resource_!=nullptr )Detach();
    
    this->resource_ = other;
    return *this;
  }
  SmartPointer(const SmartPointer &other) {
    if(other.resource_!=nullptr)
    {
      cant_ref[other.resource_]++;
      this->resource_ = other.resource_;
    }
  }

  /* Helper Function: Obtener recurso.
   * Uso: Type* p=GetPointer();
   * ------------------------------------------------------------
   * Retorna una variable puntero al recurso administrado.
   */
  Type *GetPointer() const { return this->resource_; }

  /* Helper Function: Obtiene conteo
   * Uso: if (ptr.GetReferenceCount()==1) // Única referencia
   * ------------------------------------------------------------
   * Retorna el número de referencias apuntando al recurso.
   */
  size_t GetReferenceCount() const { 
    if(cant_ref.count(this->resource_))return cant_ref[this->resource_];
     return 0;
  }
  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */
  void Detach() {
    cant_ref[this->resource_]--;
      if(!cant_ref[this->resource_])
      {
        Type *aux = nullptr;
        aux =this->resource_;
        cant_ref.erase(this->resource_);
        delete aux;
      }
    this->resource_=nullptr;
  }
};
template<class T>
map<T*,int> SmartPointer<T>::cant_ref;
#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_
