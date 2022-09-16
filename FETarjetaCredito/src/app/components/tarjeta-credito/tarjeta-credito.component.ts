import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms'
import { ToastrService } from 'ngx-toastr';
import { TarjetaService } from 'src/app/services/tarjeta.service';

@Component({
  selector: 'app-tarjeta-credito',
  templateUrl: './tarjeta-credito.component.html',
  styleUrls: ['./tarjeta-credito.component.css']
})
export class TarjetaCreditoComponent implements OnInit {
  listTarjetas: any[] = [];
  form: FormGroup;
  accion: string = "Agregar";
  id: number | undefined;

  constructor(private fb: FormBuilder,
              private toastr: ToastrService,
              private tarjetaService: TarjetaService)
  {
    this.form = this.fb.group({
      titular: ['', Validators.required],
      numeroTarjeta: ['', [Validators.required, Validators.maxLength(16), Validators.minLength(16)]],
      fechaExpiracion: ['', [Validators.required, Validators.maxLength(5), Validators.minLength(5)]],
      cvv: ['', [Validators.required, Validators.maxLength(3), Validators.minLength(3)]]
    });
  }

  ngOnInit(): void {
    this.obtenerTarjetas();
  }

  /**
   * se ha hecho "submit" en el formulario de tarjeta
   * 1. se puede guardar nueva tarjeta
   * 2. se puede actualizar tarjeta existente
   */
   guardarTarjetaSubmitButtonClicked() {
    const tarjeta = this.getCurrentTarjetaFromForm();
    if (this.id === undefined) {
      // agregamos una tarjeta nueva
      this.addNewTarjeta(tarjeta);
    } else {
      // editamos una tarjeta existente
      this.updateExistingTarjeta(tarjeta);
    }
  }

  /**
   * se ha hecho click en el botón de "editar" tarjeta
   */
   editarTarjetaButtonClicked(tarjeta: any) {
    this.accion = "Editar";
    this.id = tarjeta.id;
    console.log("selected id: " + this.id);
    this.displayTarjetaInForm(tarjeta);
  }

  /**
   * se ha hecho "click" en el botón de "eliminar" tarjeta
   */
   eliminarTarjetaButtonClicked(id: number) {
    this.tarjetaService.deleteTarjeta(id).subscribe({
      next: c => {
        // en este punto la tarjeta ya fue eliminada
        this.tarjetaDeleted();
      },
      error: e => {
        // en este punto la tarjeta no pudo ser eliminada
        this.tarjetaDeletedError(e.message);
      },
      complete: () => {
        console.log("Request completed");
      }
    });
  }

  /**
   * muestra todas las tarjetas de la base de datos en la tabla de datos
   */
   obtenerTarjetas() {
    this.tarjetaService.getListTarjetas().subscribe({
      next: c => {
        // en este punto ya tenemos la lista de tarjetas descargada del servidor
        this.listTarjetas = c;
      },
      error: e => {
        // en este punto no se pudo obtener la descarga de las tarjetas del servidor
        this.obtenerTarjetasError(e.message);
      },
      complete: () => {
        console.log("Request completed");
      }
    });
  }

  /**
   * obtiene la tarjeta que está siendo representada en el form
   */
   getCurrentTarjetaFromForm(): any {
    return {
      id: this.id, // the "id" comes from selected tarjeta in table
      titular: this.form.get("titular")?.value,
      numeroTarjeta: this.form.get("numeroTarjeta")?.value,
      fechaExpiracion: this.form.get("fechaExpiracion")?.value,
      cvv: this.form.get("cvv")?.value
    };
  }

  /**
   * agrega una nueva tarjeta a la base de datos
   */
  addNewTarjeta(tarjeta: any) {
    this.tarjetaService.saveTarjeta(tarjeta).subscribe({
      next: c => {
        // en este punto la tarjeta ya fue grabada en la base de datos
        this.tarjetaSaved();
      },
      error: e => {
        // en este punto la tarjeta no fue grabada en la base de datos
        this.tarjetaSavedError(e.message);
      },
      complete: () => {
        console.log("Request completed");
      }
    });
  }

  /**
   * actualiza una tarjeta existente
   */
   updateExistingTarjeta(tarjeta: any) {
    if (this.id !== undefined) {
      console.log("intentando actualizar");
      this.tarjetaService.updateTarjeta(this.id, tarjeta).subscribe({
        next: C => {
          // en este punto la tarjeta ya fue modificada en la base de datos
          this.tarjetaUpdated();
        },
        error: e => {
          // en este punto la tarjeta no pudo ser modificada en la base de datos
          this.tarjetaUpdatedError(e.message);
        },
        complete: () => {
          console.log("Request completed");
        }
      });
    }
  }

  /**
   * muestra una tarjeta en el form
   */
   displayTarjetaInForm(tarjeta: any) {
    this.form.patchValue({
      titular: tarjeta.titular,
      numeroTarjeta: tarjeta.numeroTarjeta,
      fechaExpiracion: tarjeta.fechaExpiracion,
      cvv: tarjeta.cvv
    });
  }

  /**
   * tarjeta se ha eliminado correctamente de la base de datos
   */
   tarjetaDeleted() {
    this.toastr.error("¡La tarjeta fue eliminada correctamente!", "Tarjeta Eliminada");
    this.obtenerTarjetas();
  }

  /**
   * la tarjeta no pudo ser eliminada
   */
   tarjetaDeletedError(message: string) {
    this.toastr.error(message, "Error de Eliminación");
  }

  /**
   * tarjeta fue guardada en la base de datos correctamente
   */
  tarjetaSaved() {
    this.toastr.success("La tarjeta fue registrada correctamente", "Tarjeta Registrada");
    this.obtenerTarjetas();
    this.form.reset();
  }

  /**
   * la tarjeta no pudo ser guardada en la base de datos
   */
  tarjetaSavedError(message: string) {
    this.toastr.error(message, "Error de Guardado");
  }

  /**
   * tarjeta fue actualizada correctamente
   */
  tarjetaUpdated() {
    this.form.reset();
    this.accion = "Agregar";
    this.id = undefined;
    this.toastr.info("La tarjeta fue actualizada correctamente", "Tarjeta Actualizada");
    this.obtenerTarjetas();
  }

  /**
   * la tarjeta no pudo ser actualizada
   */
  tarjetaUpdatedError(message: string) {
    this.toastr.error(message, "Error de Actualización");
  }

  /**
   * la tarjeta no pudo ser guardada en la base de datos
   */
   obtenerTarjetasError(message: string) {
    this.toastr.error(message, "Error de Lectura");
  }
}
