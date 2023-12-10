#include <telebot.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

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
