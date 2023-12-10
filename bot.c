#include <telebot.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

// структура для хранения информации о фотографии
typedef struct {
    char *url;
    char *filename;
} photo_info_t;

// функция для получения URL фотографии города
char *get_city_photo_url(const char *city_name) {
    // формируем URL запроса к API OpenWeatherMap
    char url[256];
    sprintf(url, "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=API_KEY", city_name);

    // выполняем запрос с помощью библиотеки libcurl
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
    curl_easy_perform(curl);

    // получаем ответ в формате JSON
    char *response = NULL;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_perform(curl);

    // парсим JSON и получаем URL фотографии города
    json_error_t error;
    json_t *root = json_loads(response, 0, &error);
    json_t *weather = json_object_get(root, "weather");
    json_t *item = json_array_get(weather, 0);
    json_t *icon = json_object_get(item, "icon");
    char *url = strdup(icon);

    // освобождаем память и закрываем соединение
    json_decref(root);
    curl_easy_cleanup(curl);
    free(response);

    return url;
}

// функция для сохранения фотографии на диск
void save_photo_to_file(const char *url, const char *filename) {
    // выполняем запрос с помощью библиотеки libcurl
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, filename);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}

// функция для отправки фотографии города
void send_city_photo(telebot_handler_t handle, long long chat_id, const char *city_name) {
    // получаем URL фотографии города
    char *url = get_city_photo_url(city_name);

    // сохраняем фотографию на диск
    char filename[256];
    sprintf(filename, "%s.jpg", city_name);
    save_photo_to_file(url, filename);

    // отправляем фотографию в чат
    telebot_send_photo(handle, chat_id, filename, NULL);

    // освобождаем память
    free(url);
    remove(filename);
}

int main() {
    // инициализация бота
    telebot_handler_t handle = telebot_create("BOT_TOKEN");

    // получение списка последних обновлений
    telebot_update_t *updates = telebot_get_updates(handle, -1, 0, 0, NULL);

    // обработка каждого сообщения
    for (int i = 0; i < telebot_array_length((void **) updates); i++) {
        telebot_update_t *update = updates[i];
        if (update->message != NULL && update->message->text != NULL) {
            char *text = update->message->text;
            // если сообщение содержит название города, отправляем фотографию
            if (strlen(text) > 2) {
                send_city_photo(handle, update->message->chat->id, text);
            }
        }
    }

    // освобождение памяти
    telebot_put_updates(updates, true);
    telebot_destroy(handle);
    return 0;
}
