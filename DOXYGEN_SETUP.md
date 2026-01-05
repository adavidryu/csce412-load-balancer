# Doxygen Documentation Setup Guide

## Installation

### macOS (using Homebrew)
```bash
brew install doxygen
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install doxygen
```

### Linux (Fedora/RHEL)
```bash
sudo dnf install doxygen
```

### Verify Installation
```bash
doxygen --version
```

## Generating Documentation

1. **Generate HTML documentation:**
   ```bash
   doxygen Doxyfile
   ```

2. **View the documentation:**
   - Open `docs/html/index.html` in a web browser
   - Or use: `open docs/html/index.html` (macOS) or `xdg-open docs/html/index.html` (Linux)

## Uploading to people.tamu.edu

1. **Compress the HTML documentation:**
   ```bash
   cd docs
   tar -czf load-balancer-docs.tar.gz html/
   # OR
   zip -r load-balancer-docs.zip html/
   ```

2. **Upload to people.tamu.edu:**
   - Use SFTP/SCP to upload the compressed file
   - Or use the web interface if available
   - Extract in your public_html directory

3. **Access the documentation:**
   - URL will be: `https://people.tamu.edu/~yourusername/load-balancer-docs/html/index.html`
   - Make sure the directory has proper permissions (chmod 755)

## Quick Commands

```bash
# Generate docs
doxygen Doxyfile

# Clean and regenerate
rm -rf docs/html
doxygen Doxyfile

# View locally
open docs/html/index.html  # macOS
xdg-open docs/html/index.html  # Linux
```

## Documentation Structure

The generated documentation includes:
- **Classes/Structs**: All classes and structures with their members
- **Files**: Documentation for each source file
- **Functions**: All functions with parameters and return values
- **Index**: Alphabetical index of all documented items

