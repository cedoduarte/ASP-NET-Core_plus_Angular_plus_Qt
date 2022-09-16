using Microsoft.AspNetCore.Mvc;
using BETarjetaCredito.Models;
using Microsoft.EntityFrameworkCore;

namespace BETarjetaCredito.Controllers
{
    [ApiController]
    [Route("tarjetacredito")]
    public class TarjetaCreditoController : ControllerBase
    {
        private readonly ApplicationDbContext ctx;

        public TarjetaCreditoController(ApplicationDbContext ctx)
        {
            this.ctx = ctx;
        }

        /**
         * gets all credit cards
         */
        [HttpGet]
        public async Task<ActionResult<IEnumerable<TarjetaCredito>>> Get()
        {
            try
            {
                var listTarjetas = await this.ctx.TarjetaCredito.ToListAsync();
                return Ok(listTarjetas);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }

        /**
         * gets a credit card by id
         */
        [HttpGet("{id:int}")]
        public async Task<ActionResult<TarjetaCredito>> Get(int id)
        {
            try
            {
                var tarjetaCredito = await this.ctx.TarjetaCredito.FirstOrDefaultAsync(x => x.Id == id);
                if (tarjetaCredito is not null)
                {
                    return Ok(tarjetaCredito);
                }
                else
                {
                    return NotFound();
                }
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }

        /**
         * inserts a new credit card
         */
        [HttpPost]
        public async Task<ActionResult<TarjetaCredito>> Post(TarjetaCredito newTarjetaCredito)
        {
            // begins the transaction
            using var txn = await this.ctx.Database.BeginTransactionAsync();
            try
            {
                // here the "newTarjetaCredito.Id" value is ignored
                await this.ctx.AddAsync(newTarjetaCredito);
                await this.ctx.SaveChangesAsync();

                // ends the transaction
                await txn.CommitAsync();

                // here "newTarjetaCredito" has a new "Id"
                return Ok(newTarjetaCredito);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }

        [HttpPut("{id:int}")]
        public async Task<ActionResult<TarjetaCredito>> Put(int id, TarjetaCredito existingTarjetaCredito)
        {
            if (id != existingTarjetaCredito.Id)
            {
                return NotFound();
            }

            // begins the transaction
            using var txn = await this.ctx.Database.BeginTransactionAsync();
            try
            {
                this.ctx.Update(existingTarjetaCredito);
                await this.ctx.SaveChangesAsync();

                // ends the transaction
                await txn.CommitAsync();

                return Ok(existingTarjetaCredito);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }

        [HttpDelete("{id:int}")]
        public async Task<ActionResult> Delete(int id)
        {
            // begins the transaction
            using var txn = await this.ctx.Database.BeginTransactionAsync();
            try
            {
                var existingTarjetaCredito = await this.ctx.TarjetaCredito.FindAsync(id);
                if (existingTarjetaCredito is null)
                {
                    return NotFound();
                }
                this.ctx.Remove(existingTarjetaCredito);
                await this.ctx.SaveChangesAsync();

                // ends the transaction
                await txn.CommitAsync();

                return Ok();
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }

        /**
         * removes the TarjetaCredito with specified "id"
         */
        [HttpPost("eliminar/{id:int}")]
        public async Task<ActionResult> PostEliminar(int id)
        {
            // begins the transaction
            using var txn = await this.ctx.Database.BeginTransactionAsync();
            try
            {
                var existingTarjetaCredito = await this.ctx.TarjetaCredito.FindAsync(id);
                if (existingTarjetaCredito is null)
                {
                    return NotFound();
                }
                this.ctx.Remove(existingTarjetaCredito);
                await this.ctx.SaveChangesAsync();

                // ends the transaction
                await txn.CommitAsync();

                return Ok();
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
        }
    }
}
