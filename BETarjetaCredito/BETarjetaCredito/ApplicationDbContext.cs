using Microsoft.EntityFrameworkCore;
using System.Reflection;
using BETarjetaCredito.Models;

namespace BETarjetaCredito
{
    public class ApplicationDbContext : DbContext
    {
        public DbSet<TarjetaCredito> TarjetaCredito { get; set; }

        public ApplicationDbContext(DbContextOptions options)
            : base(options)
        {
            // nothing to do here
        }

        protected override void OnConfiguring(DbContextOptionsBuilder builder)
        {
            if (!builder.IsConfigured)
            {
                builder.UseSqlServer("name=DefaultConnection").UseQueryTrackingBehavior(QueryTrackingBehavior.NoTracking);
            }
        }

        protected override void ConfigureConventions(ModelConfigurationBuilder builder)
        {
            builder.Properties<DateTime>().HaveColumnType("date");
        }

        protected override void OnModelCreating(ModelBuilder builder)
        {
            base.OnModelCreating(builder);

            // you can use this reflection instruction for finding automatically the configuration classes
            builder.ApplyConfigurationsFromAssembly(Assembly.GetExecutingAssembly());

            // set URL properties as not unicode
            foreach (var entType in builder.Model.GetEntityTypes())
            {
                foreach (var prop in entType.GetProperties())
                {
                    if (prop.ClrType == typeof(string) && prop.Name.Contains("URL", StringComparison.CurrentCultureIgnoreCase))
                    {
                        prop.SetIsUnicode(false);
                        prop.SetMaxLength(500);
                    }
                }
            }
        }
    }
}
