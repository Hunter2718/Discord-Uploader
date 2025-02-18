# Discord-Uploader

A lightweight **CLI tool** for automating file uploads to Discord via webhooks. Designed to be easily used as a **plugin for larger projects**, `Discord-Uploader` provides a simple way to send files, text, and JSON payloads to Discord.

## 🚀 Features
- **Simple CLI usage** – Easily integrate into other programs
- **Supports file, text, and JSON uploads** to Discord webhooks
- **Standalone executable** – No need for additional installations
- **Uses libcurl** for cross-platform compatibility (Linux supported, Windows/macOS coming soon)

- **Future Plans**:
  - GUI version
  - Windows/macOS support
  - File splitting for large uploads

## 👥 Installation
Currently, **only Linux** is supported for the easy install method.

### 🔹 Easy Install (Recommended)
1. Download the latest binary from the [Releases page](https://github.com/Hunter2718/Discord-Uploader/releases).
2. Place the executable in a directory included in your system `PATH`.
3. Run the program using the command-line options below.

### 🔸 Hard Install (Compile from Source)
> **Not recommended unless modifying the source code.**
1. Clone the repository:
   ```sh
   git clone https://github.com/Hunter2718/Discord-Uploader.git
   cd Discord-Uploader
   ```
2. Install `libcurl` if not already installed:
   ```sh
   sudo apt install libcurl4-openssl-dev  # Debian/Ubuntu
   ```
3. Compile using `gcc`:
   ```sh
   gcc -o discord-uploader main.m -lcurl
   ```

## ⚡ Usage
```sh
./discord-uploader --file {pathToFile, optional} \
                   --json {jsonString, optional} \
                   --text {textString, optional} \
                   --webhook {discordWebhook, required} \
                   --help {showsHelpMessage, optional}
```
> **Note:** At least one of `--file`, `--json`, or `--text` must be provided.

### 📌 Example Usage
#### Sending a text message
```sh
./discord-uploader --text "Hello from CLI!" --webhook "YOUR_WEBHOOK_URL"
```

#### Uploading a file
```sh
./discord-uploader --file "./example.png" --webhook "YOUR_WEBHOOK_URL"
```

#### Sending a JSON payload
```sh
./discord-uploader --json '{"content": "Hello, JSON!"}' --webhook "YOUR_WEBHOOK_URL"
```

## 📢 Setting Up a Discord Webhook
1. Open **Discord** and go to your server settings.
2. Navigate to **Integrations > Webhooks**.
3. Create a new webhook and copy the **Webhook URL**.
4. Use this URL with `Discord-Uploader` to send messages.

For a detailed guide, see: [How to Create a Discord Webhook](https://techwiser.com/create-discord-webhook-send-message/).

## ❗ Limitations
- **Maximum file size:** Discord allows files up to **8MB** for free users.
- **Rate limits:** Discord enforces webhook rate limits (5 requests per second).
- **Currently, only Linux supports the easy install.** Windows/macOS support is planned.

## 🛠 Troubleshooting
### "Webhook is required" error
Ensure you provide a valid webhook URL using `--webhook`.

### "File not found" error
Check that the file path is correct and that the file exists.

### "JSON format error"
Ensure the JSON string is properly formatted. Test it with a JSON validator.

## 🎥 Demo
*Coming soon – GIF demonstration of usage.*

## 🤝 Contributing
Contributions are welcome! Please see our **[CONTRIBUTING.md](CONTRIBUTING.md)** for guidelines.

## ⚖️ License
See **[LICENSE.md](LICENSE.md)** for more details.
