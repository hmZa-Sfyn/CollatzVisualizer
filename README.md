# 🚀 Collatz Visualizer

A **C++ application** that simulates the Collatz (3x+1) conjecture, stores results in JSON files, and provides a web interface to visualize sequences in real time.

---

## 📦 Description

**CollatzVisualizer** is a C++ web server that:
- Computes the **Collatz sequence** for a given number.
- Saves it to `./computated/<number>.json`.
- Serves a live webpage with a **Chart.js line graph** and output data.

---

## 🧰 Prerequisites

### ✅ OS
- Linux (tested on Ubuntu; adaptable)

### ✅ Dependencies

- <code>g++</code> (C++17-compatible compiler)
- <code>libboost-all-dev</code>
- <code>git</code>, <code>curl</code>

### ✅ Libraries

- <code>Crow</code> (v1.2.0) — single header web framework
- <code>nlohmann/json</code> (v3.11.3)

---

## 🛠️ Installation

### 🔁 Clone the Repository

<code>
git clone https://github.com/your-username/CollatzVisualizer.git  
cd CollatzVisualizer
</code>

### ⚙️ Run the Setup Script

<code>
chmod +x setup_and_run.sh  
./setup_and_run.sh --install
</code>

This will:
- Install packages and dependencies
- Download headers
- Compile the server
- Create `computated/` output folder

---

## 🧪 Example Output

File: <code>./computated/6.json</code>

<code>
{
  "number": 6,
  "sequence": [6, 3, 10, 5, 16, 8, 4, 2, 1],
  "steps": 8,
  "max_value": 16
}
</code>

---

## 🧑‍💻 Running the App

### ▶️ Start Web Server

<code>
./setup_and_run.sh --run
</code>

Open your browser and go to:  
<code>http://localhost:8080</code>

### 🧮 Interface Features

- Input any number.
- Visualize the sequence steps.
- See chart and JSON output.
- JSON is saved to <code>./computated/</code>.

---

## 📋 Usage Options

<code>
./setup_and_run.sh --help  
</code>

- <code>--install</code> : Install and compile  
- <code>--run</code> : Start the web server  
- <code>--clean</code> : Remove the compiled binary

---

## ❓ Troubleshooting

### curl (23) error:
<code>sudo chmod -R u+w include</code>

Or download manually:

<code>
mkdir -p include/nlohmann  
curl -L https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp -o include/nlohmann/json.hpp
</code>

### asio.hpp missing?
<code>sudo apt-get install -y libboost-all-dev</code>

---

## 📂 Project Structure

<code>
CollatzVisualizer/  
├── collatz_webserver.cpp  
├── setup_and_run.sh  
├── computated/  
├── include/  
│   ├── crow.h  
│   └── nlohmann/  
│       └── json.hpp  
</code>

---

## 🤝 Contributing

PRs and issues welcome on GitHub.

---

## 📄 License

MIT License.
