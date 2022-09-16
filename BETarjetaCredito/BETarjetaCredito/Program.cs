using BETarjetaCredito;
using Microsoft.EntityFrameworkCore;
using System.Text.Json.Serialization;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddControllers().AddJsonOptions(opt =>
{
    opt.JsonSerializerOptions.ReferenceHandler = ReferenceHandler.IgnoreCycles;
});

builder.Services.AddControllers();
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

// enables Cross-Origin Requests (CORS) in ASP.NET Core
builder.Services.AddCors(options => options.AddPolicy("AllowWebApp", builder => builder.AllowAnyOrigin().AllowAnyHeader().AllowAnyMethod()));

// configures the ApplicationDbContext as a service
var connectionString = builder.Configuration.GetConnectionString("DefaultConnection");
builder.Services.AddDbContextFactory<ApplicationDbContext>(opt =>
{
    // specifies the usage of MSSQLServer
    opt.UseSqlServer(connectionString);

    // disables the tracking for improving the performance
    opt.UseQueryTrackingBehavior(QueryTrackingBehavior.NoTracking);
});

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

// uses Cross-Origin Requests (CORS) in ASP.NET Core
app.UseCors("AllowWebApp");
// the BackEnd is ready to communicate with the FrontEnd (for example Angular)

app.UseHttpsRedirection();

app.UseAuthorization();

app.MapControllers();

app.Run();
