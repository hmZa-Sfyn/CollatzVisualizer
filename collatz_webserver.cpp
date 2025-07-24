#include <crow.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

using json = nlohmann::json;

void computeCollatz(long long n, std::vector<long long>& sequence, long long& steps, long long& max_val) {
    sequence.push_back(n);
    steps = 0;
    max_val = n;
    
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        sequence.push_back(n);
        steps++;
        if (n > max_val) {
            max_val = n;
        }
    }
}

void saveToJson(long long n, const std::vector<long long>& sequence, long long steps, long long max_val) {
    json j;
    j["number"] = n;
    j["sequence"] = sequence;
    j["steps"] = steps;
    j["max_value"] = max_val;

    std::filesystem::create_directory("./computated");
    std::ofstream file("./computated/" + std::to_string(n) + ".json");
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    }
}

std::string getCollatzHtml(long long n) {
    std::vector<long long> sequence;
    long long steps, max_val;
    computeCollatz(n, sequence, steps, max_val);
    saveToJson(n, sequence, steps, max_val);

    std::stringstream html;
    html << "<!DOCTYPE html><html><head><title>Collatz Visualizer</title>";
    html << "<style>body { font-family: Arial; margin: 20px; }";
    html << "input { padding: 5px; margin: 10px; }";
    html << "#chart { width: 100%; height: 400px; }";
    html << "</style>";
    html << "<script src='https://cdn.jsdelivr.net/npm/chart.js'></script></head>";
    html << "<body><h1>Collatz Sequence Visualizer</h1>";
    html << "<form action='/collatz' method='GET'>";
    html << "<input type='number' name='n' placeholder='Enter a positive integer' required>";
    html << "<input type='submit' value='Generate Sequence'>";
    html << "</form>";
    html << "<h2>Sequence for " << n << "</h2>";
    html << "<p>Steps: " << steps << ", Max Value: " << max_val << "</p>";
    html << "<p>Sequence: ";
    for (size_t i = 0; i < sequence.size(); ++i) {
        html << sequence[i];
        if (i < sequence.size() - 1) html << ", ";
    }
    html << "</p>";
    html << "<canvas id='chart'></canvas>";
    html << "<script>";
    html << "const ctx = document.getElementById('chart').getContext('2d');";
    html << "const chart = new Chart(ctx, {";
    html << "type: 'line', data: { labels: [";
    for (size_t i = 0; i < sequence.size(); ++i) {
        html << "'" << i << "'";
        if (i < sequence.size() - 1) html << ",";
    }
    html << "], datasets: [{ label: 'Collatz Sequence', data: [";
    for (size_t i = 0; i < sequence.size(); ++i) {
        html << sequence[i];
        if (i < sequence.size() - 1) html << ",";
    }
    html << "], borderColor: 'blue', fill: false }]},";
    html << "options: { scales: { y: { beginAtZero: false }}}});</script>";
    html << "</body></html>";
    return html.str();
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "<!DOCTYPE html><html><head><title>Collatz Visualizer</title>"
               "<style>body { font-family: Arial; margin: 20px; }"
               "input { padding: 5px; margin: 10px; }</style></head>"
               "<body><h1>Collatz Sequence Visualizer</h1>"
               "<form action='/collatz' method='GET'>"
               "<input type='number' name='n' placeholder='Enter a positive integer' required>"
               "<input type='submit' value='Generate Sequence'>"
               "</form></body></html>";
    });

    CROW_ROUTE(app, "/collatz")([] (const crow::request& req) {
        auto n_str = req.url_params.get("n");
        if (!n_str) {
            return crow::response(400, "Please provide a number 'n' in the query string.");
        }
        try {
            long long n = std::stoll(n_str);
            if (n <= 0) {
                return crow::response(400, "Please enter a positive integer.");
            }
            return crow::response(getCollatzHtml(n));
        } catch (...) {
            return crow::response(400, "Invalid number format.");
        }
    });

    app.port(8080).multithreaded().run();
    return 0;
}