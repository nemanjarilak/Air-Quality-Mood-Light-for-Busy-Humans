

---

# Air Quality Mood Light for Busy Humans 🌈🤖

Meet your new passive-aggressive air quality monitor! This ESP8266-based project transforms boring pollution data into a colorful light show that's easier to read than your ex's mixed signals. Perfect for people who:

- Want to know if they should breathe today... at a glance
- Think OLED displays are for overachievers
- Believe RGB LEDs make everything better
- Enjoy their furniture judging their life choices

## Features ✨

- **Real-time air quality updates** (every 30 minutes - we're not running a hospital here)
- **Soothing color transitions** (like a lava lamp, but for existential dread)
- **Dramatic breathing effects** (for when the AQI hits "are we in Beijing?")
- **Passive monitoring** (it judges silently)
- **WiFi auto-reconnect** (more reliable than your dating life)

## Why LEDs? 💡

Who has time to read numbers? We've got colors!
- Green: "Yay, photosynthesis mode activated!"
- Blue: "Could be worse..."
- Red: "Congratulations! You've achieved soup atmosphere"


## AQI Color Decoder 🎨🌪️  
(Now With 100% More Existential Dread!)

Our *artistically liberal* color scheme translates government air metrics into emotional damage:

- **🟢 Green Solid (0-50 AQI)**  
"Fresh as a mountain breeze" (that exists only in Tesla commercials)  
*Translation:* "You could almost pretend we're not doomed!"

- **🟢💚 Green Breathing (51-100)**  
"Moderate" - Nature's way of saying "I'm fine" through clenched teeth  

- **🔵 Blue Solid (101-150)**  
"Unhealthy for sensitive groups" (aka everyone under 30)  
*Real talk:* Your plants are judging your life choices

- **🔵💙 Blue Breathing (151-200)**  
"Unhealthy" - Congratulations, we're all sensitive now!  
*Pro tip:* Great time to take up mouth breathing

- **🔴 Red Solid (201-300)**  
"Very Unhealthy" - Air so thick you could chew it  
*Suggested response:* Practice your Darth Vader impressions

- **🔴❤️ Red Breathing (300+)**  
"Hazardous" - Basically breathing lentil soup  
*Emergency protocol:* Become amphibious immediately

*Disclaimer:* This color scheme approved by no one but my LED strip. For actual science, maybe don't trust blinking lights.

## Setup Instructions 🛠️

### 1. API Key Acquisition (Free!)
1. Visit [AirVisual API Portal](https://www.iqair.com/air-pollution-data-api)
2. Sign up like you're joining a secret society
3. Get your FREE API key (no credit card required - we're not monsters)

### 2. Hardware Hookup (No PhD Required)
**You'll need:**
- ESP8266 NodeMCU (I used this board, but any ESP8266 will work)
- Common cathode RGB LED (the drama queen of components)

**Wiring Guide:**
```
LED      -> ESP8266
--------------------
Red      -> D5 (GPIO14)
Green    -> D6 (GPIO12)
Blue     -> D7 (GPIO13)
Ground   -> GND (Any ground pin)
```

*Pro tip: Add 220Ω resistors unless you like LED funeral pyres*

### 3. Software Setup
1. Replace these in the code like you're Jason Bourne:
```cpp
const char* ssid = "SSID";          // Your WiFi name
const char* password = "PASS";   // WiFi password (RIP your security)
const String API_KEY = "your_key_here"; // From step 1
const float LATITUDE = 40.000000;    // Your crib's coordinates
const float LONGITUDE = 20.000000;   // Get these from Google Maps
```

### 4. Deployment
1. Upload code while making hacker noises
2. Plug it in near your plants so they know air quality too
3. Bask in the glow of environmental awareness

## FAQ (Frequently Avoided Questions)

❓ *Why not OLED?*  
Because subtlety is for libraries. I want to know if I'm dying from across the room!

❓ *Why ESP8266?*  
It's cheaper than a Starbucks latte and smarter than your ex.

❓ *Won't the LED burn out?*  
Only if the air quality gets REALLY bad. Consider it a feature.

---

**Disclaimer:** Persistent red light may cause sudden urges to become a climate activist. Not responsible for LED-induced paranoia. If blinking continues for more than 4 hours, consult your local meteorologist.
