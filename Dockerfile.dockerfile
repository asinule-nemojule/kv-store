# Koristimo Ubuntu kao osnovu
FROM ubuntu:22.04

# Instaliramo potrebne biblioteke
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Kopiramo naš program u kontejner
COPY kv_server /app/kv_server

# Otvaramo port 8080
EXPOSE 8080

# Pokrećemo server kada se kontejner startuje
CMD ["/app/kv_server"]