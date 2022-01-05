#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment {
    private:
        //environment logic
        struct Weather {
            bool sun;
            bool rain;
        };
        Weather weather;
        // TODO: day/night timer
        bool daytime;

        // functions
        void initWeather();
        void initTime();
    public:
        // constructors and deconstructors
        Environment();
        virtual ~Environment();

        // getters
        const bool getSun() const;
        const bool getRain() const;
        const bool isDaytime() const;
};

#endif