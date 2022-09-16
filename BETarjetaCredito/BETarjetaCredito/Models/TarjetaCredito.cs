namespace BETarjetaCredito.Models
{
    public class TarjetaCredito
    {
        public int Id { get; set; }
        public string? Titular { get; set; }
        public string? NumeroTarjeta { get; set; }
        public string? FechaExpiracion { get; set; }
        public string? CVV { get; set; }
    }
}
