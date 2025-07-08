#include <string>
#include <iostream>
#include <vector>

/*

        JsonBuilder jsonBuilder;
        jsonBuilder
            .addString("nickname", playerName)
            .addInt("playerId", playerId);

        std::string jsonString = jsonBuilder.build();

 */

class JsonBuilder {
public:
    JsonBuilder() {
        jsonString = "{";
    }

    JsonBuilder& addInt(const std::string& key, int32_t value) {
        addCommaIfNeeded();
        jsonString += "\"" + key + "\":" + std::to_string(value);
        return *this;
    }

    JsonBuilder& addFloat(const std::string& key, float value) {
        addCommaIfNeeded();
        jsonString += "\"" + key + "\":" + std::to_string(value);
        return *this;
    }

    JsonBuilder& addBool(const std::string& key, bool value) {
        addCommaIfNeeded();
        jsonString += "\"" + key + "\":" + (value ? "true" : "false");
        return *this;
    }

    JsonBuilder& addString(const std::string& key, const std::string& value) {
        addCommaIfNeeded();
        jsonString += "\"" + key + "\":\"" + escapeString(value) + "\"";
        return *this;
    }

    JsonBuilder& addArray(const std::string& key = "") {
        addCommaIfNeeded();
        if (!key.empty()) {
            jsonString += "\"" + key + "\":[";
        } else {
            jsonString += "[";
        }
        inArray = true;
        return *this;
    }

    JsonBuilder& endArray() {
        if (inArray) {
            jsonString += "]";
            inArray = false;
        }
        return *this;
    }

    std::string build() {
        jsonString += "}";
        return jsonString;
    }

private:
    std::string jsonString;
    bool firstElement = true;
    bool inArray = false;

    void addCommaIfNeeded() {
        if (!firstElement) {
            jsonString += ",";
        }
        firstElement = false;
    }

    void addCommaIfNeededInArray() {
        if (jsonString.back() != '[') {
            jsonString += ",";
        }
    }

    std::string escapeString(const std::string& value) const {
        std::string escaped = value;
        size_t pos = 0;
        while ((pos = escaped.find('"', pos)) != std::string::npos) {
            escaped.replace(pos, 1, "\\\"");
            pos += 2;
        }
        pos = 0;
        while ((pos = escaped.find('\\', pos)) != std::string::npos) {
            escaped.replace(pos, 1, "\\\\");
            pos += 2;
        }
        return escaped;
    }
};