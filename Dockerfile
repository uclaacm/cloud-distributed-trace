FROM gcc:latest

# Set working directory
WORKDIR /app

# Copy all files to the working directory
COPY . /app/

RUN ls -l /app

# Make shell scripts executable
RUN chmod +x libcompile.sh srccompile.sh testcompile.sh

# Run the scripts
RUN ./libcompile.sh
RUN ./srccompile.sh
RUN ./testcompile.sh

# Keep the container running for debugging purposes
CMD ["tail", "-f", "/dev/null"]