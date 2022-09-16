using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace BETarjetaCredito.Models.Config
{
    public class TarjetaCreditoConfig : IEntityTypeConfiguration<TarjetaCredito>
    {
        public void Configure(EntityTypeBuilder<TarjetaCredito> builder)
        {
            builder.HasKey(x => x.Id);
            builder.Property(x => x.Titular).IsRequired(true).HasMaxLength(250);
            builder.Property(x => x.NumeroTarjeta).IsRequired(true).HasMaxLength(16);
            builder.Property(x => x.FechaExpiracion).IsRequired(true).HasMaxLength(5);
            builder.Property(x => x.CVV).IsRequired(true).HasMaxLength(3);
        }
    }
}
