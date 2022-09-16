import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

// Los 3 usos más típicos de los servicios en Angular:
// 1. los servicios son utilizados para hacer peticiones "http" a algún "backend"
// 2. reutilización de código entre componentes
// 3. comunicación de datos entre componentes

@Injectable({
  providedIn: 'root'
})
export class TarjetaService {
  private myAppUrl: string = "https://localhost:7211";
  private myApiUrl: string = "/tarjetacredito/";

  constructor(private http: HttpClient) {    
  }
  
  getListTarjetas(): Observable<any> {
    return this.http.get(this.myAppUrl + this.myApiUrl);    
  }
}
