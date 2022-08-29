class Button
{
    private:
        const p;
        short deb_time = 100;
        long t;

    public:
        Button(const pin)
        {
            p = pin;
        }
        bool click(bool hold_count)
        {
            if(hold_count)
            {
                if(digitalRead(p))
                {
                    if((millis() - t) >= deb_time)
                    {
                        t = millis();
                        return true;
                    }
                }
            }else
            {
                if(digitalRead(p))
                {
                    if((millis() - t) >= deb_time)
                    {
                        t = millis();
                        return true;
                    }
                    t = millis();
                }
            }
            return false;
        }

};