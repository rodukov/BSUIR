#include <iostream>
#include <string>
using namespace std;

class Media {
protected:
    string title;
    double duration; // в минутах

public:
    Media(const string& t, double d) : title(t), duration(d) {}
    virtual ~Media() {}

    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;

    virtual void info() const {
        cout << "Название: " << title << "\n"
            << "Длительность: " << duration << " мин\n";
    }
};

class IDownloadable {
public:
    virtual void download() = 0;
    virtual bool isDownloaded() const = 0;
    virtual ~IDownloadable() {}
};

// Класс Audio
class Audio : public Media, public IDownloadable {
private:
    double fileSize;
    bool downloaded;

public:
    Audio(const string& t, double d, double size)
        : Media(t, d), fileSize(size), downloaded(false) {
    }

    void play() override {
        cout << "Воспроизведение аудио: " << title << endl;
    }

    void pause() override {
        cout << "Пауза аудио: " << title << endl;
    }

    void stop() override {
        cout << "Остановлено аудио: " << title << endl;
    }

    void download() override {
        downloaded = true;
        cout << "Аудио \"" << title << "\" скачано (" << fileSize << " МБ)" << endl;
    }

    bool isDownloaded() const override {
        return downloaded;
    }

    void info() const override {
        Media::info();
        cout << "Тип: Audio\nРазмер: " << fileSize << " МБ\n"
            << "Статус: " << (downloaded ? "Скачано" : "Не скачано") << "\n";
    }
};

// Класс Video
class Video : public Media, public IDownloadable {
private:
    double fileSize; // МБ
    bool downloaded;

public:
    Video(const string& t, double d, double size)
        : Media(t, d), fileSize(size), downloaded(false) {
    }

    void play() override {
        cout << "Воспроизведение видео: " << title << endl;
    }

    void pause() override {
        cout << "Пауза видео: " << title << endl;
    }

    void stop() override {
        cout << "Остановлено видео: " << title << endl;
    }

    void download() override {
        downloaded = true;
        cout << "Видео \"" << title << "\" скачано (" << fileSize << " МБ)" << endl;
    }

    bool isDownloaded() const override {
        return downloaded;
    }

    void info() const override {
        Media::info();
        cout << "Тип: Video\nРазмер: " << fileSize << " МБ\n"
            << "Статус: " << (downloaded ? "Скачано" : "Не скачано") << "\n";
    }
};

// Тестирование
int main() {
    setlocale(LC_ALL, "");
    Audio song("Pink Floyd - Time", 6.5, 8.2);
    Video movie("Interstellar", 169.0, 1200.0);

    song.download();
    movie.download();

    cout << "\nИнформация о медиатеках:\n";
    song.info();
    cout << endl;
    movie.info();

    cout << "\nДемонстрация воспроизведения:\n";
    song.play();
    song.pause();
    song.stop();

    cout << endl;
    movie.play();
    movie.pause();
    movie.stop();

    return 0;
}
