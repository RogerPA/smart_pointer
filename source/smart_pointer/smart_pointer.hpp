// Copyright 2020 Roger Peralta Aranibar
#ifndef SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#define SOURCE_SMART_POINTER_SMART_POINTER_HPP_
#include <cstddef>



class ContadorReferencias
{
    private:
    // Contador
    int count; 

    public:
    
    ContadorReferencias():count(0){}
    
    // Incremento del contador de referencias
    void AddRef(){
      ++count;
    }

    //Decrementa el conteo de referencias
    void SubtRef(){
      --count;
    }

    //retornar el contador de referencias
    int getContador(){
        return count;
    }

    ~ContadorReferencias(){}
};

/*
 * Smart Pointer que implementa un tipo de estrategia por conteo de referencias.
 * Permite que varios SmartPointers puedan acceder al mismo recurso compartido.
 * Cuando el ˙ltimo puntero es eliminado, se elimina y libera el recurso.
 */
template <typename Type>
class SmartPointer {
 private:
  Type *resource_;
  ContadorReferencias *referencia;
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
    this->referencia = new ContadorReferencias();
    this->referencia->AddRef();
  }

   explicit SmartPointer() : resource_(nullptr) {
    referencia=new ContadorReferencias();
    referencia->AddRef();
  }

  /* Destructor: ~SmartPointer();
   * Uso: (implícito)
   * ------------------------------------------------------------
   * Decrementa el contador de referencias del recurso, eliminando
   * y liberando la memoria si fuera el último SmartPointer apuntando
   * al recurso.
   */
  ~SmartPointer() {
    this->referencia->SubtRef();

    if (referencia->getContador() == 0)
    {
      delete this->resource_;
      delete this->referencia;
    }
  }

  /* SmartPointer operadores de "des-referencia"(dereference)
   * Uso: cout << *myPtr << endl;
   * Uso: cout << myPtr->length << endl;
   * ------------------------------------------------------------
   * Permite al SmartPointer comportarse como si fuera un puntero.
   */
  Type &operator*() const { 
    return *resource_; 
  }

  Type *operator->() const { 
    return resource_;
  }

  
  
  /* Funciones de copia
   * Uso: SmartPointer<string> ptr=existingPointer;
   *      ptr=existingPtr;
   * ------------------------------------------------------------
   * Cambia el recurso referenciado por este SmartPointer por otro
   * SmartPointer. Si el conteo llega a cero, debe ser eliminado
   * (deallocated).
   */
  SmartPointer &operator=(const SmartPointer &other) { 
    if (this != &other)
     {
       //Reducimos porque haremos un cambio de referencia
       referencia->SubtRef();

       //Como es una copia debemos liberar la memoria si no existe ningun puntero a ese dato
       if (referencia->getContador()==0)
       {
         delete resource_;
         delete referencia;
       }
       
       //Apuntar al mismo dato
       //Cambio de referencia 
       resource_=other.resource_;
       referencia=other.referencia;
       referencia->AddRef();
     }
     return *this;
   }

  
  SmartPointer &operator=(Type *other) { 
    //Falta Modificar
    if (resource_ != other)
     {
       //Reducimos porque haremos un cambio de referencia
       referencia->SubtRef();

       //Como es una nueva signacion debemos liberar la memoria si no existe ningun puntero a ese dato
       if (referencia->getContador()==0)
       {
         delete resource_;
         delete referencia;
       }
       
       resource_=other;
       referencia=new ContadorReferencias();
       referencia->AddRef();
     }
     return *this;
  }
  

  //Constructor Copia
  // Copia datos,puntero referencia y incrementar el contador de referencia
  SmartPointer(const SmartPointer &other) {
    resource_=other.resource_;
    referencia=other.referencia;
    referencia->AddRef();
  }

  /* Helper Function: Obtener recurso.
   * Uso: Type* p=GetPointer();
   * ------------------------------------------------------------
   * Retorna una variable puntero al recurso administrado.
   */
  Type *GetPointer() const { 
    return resource_; }

  /* Helper Function: Obtiene conteo
   * Uso: if (ptr.GetReferenceCount()==1) // Única referencia
   * ------------------------------------------------------------
   * Retorna el número de referencias apuntando al recurso.
   */

  //ConstructorFuncionality
  size_t GetReferenceCount() const { 
    return referencia->getContador(); 
  }




  /* Helper Function: se des-asocia del recurso;
   * Uso: ptr.Detach();
   * ------------------------------------------------------------
   * Deja de administrar un recurso. eliminando y liberando la
   * memoria si es necesario.
   */
  void Detach() {}
};

#endif  // SOURCE_SMART_POINTER_SMART_POINTER_HPP_