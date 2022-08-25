import Adafruit_PCA9685
import time

class MG90_96R_Class:
    def __init__(self, Channel, ZeroOffset):
        self.servo_num = Channel
        self.servo_offset = ZeroOffset

        # 원하는 주소 및/또는 버스를 사용하여 PCA9685를 초기화합니다.
        self.Pwm = Adafruit_PCA9685.PCA9685(address = 0x40, busnum = 1)

        # 주파수를 60[Hz]로 설정
        self.Pwm.set_pwm_freq(60)

# 최소 및 최대 서보 펄스 길이 구성
# 150 최소 펄스 길이
# 650 최대 펄스 길이
    def SetPos(self, pos):
        pulse = (650 - 150) * pos / 180 + 150 + self.servo_offset
        self.Pwm.set_pwm(self.servo_num, 0, int(pulse))

    def Cleanup(self):
        self.SetPos(90)
        time.sleep(1)

if __name__ == '__main__':
    Servo0 = MG90_96R_Class(Channel = 0, ZeroOffset = -10)
    Servo1 = MG90_96R_Class(Channel = 1, ZeroOffset = -10)
    Servo2 = MG90_96R_Class(Channel = 2, ZeroOffset = -10)
    Servo3 = MG90_96R_Class(Channel = 3, ZeroOffset = -10)
    Servo4 = MG90_96R_Class(Channel = 4, ZeroOffset = -10)
    Servo5 = MG90_96R_Class(Channel = 5, ZeroOffset = -10)
    Servo6 = MG90_96R_Class(Channel = 6, ZeroOffset = -10)

    try:
         while True:
            ch = input("input : ")
            # up
            # 상체
            if ch == 'q':
                Servo0.SetPos(90)
                Servo1.SetPos(90)
                time.sleep(1)

            if ch == 'w':
                Servo2.SetPos(180)
                Servo3.SetPos(180)
                time.sleep(1)
            # 다리
            if ch == 'r':
                Servo4.SetPos(120)
                Servo5.SetPos(120)
                time.sleep(1)

            # 등받이
            if ch == 't':
                Servo6.SetPos(150)
                time.sleep(1)

            # down
            if ch == 'a':
                Servo0.SetPos(180)
                Servo1.SetPos(180)
                time.sleep(1)

            if ch == 's':
                Servo2.SetPos(90)
                Servo3.SetPos(90)
                time.sleep(1)

            if ch == 'f':
                Servo4.SetPos(90)
                Servo5.SetPos(90)
                time.sleep(1)

            if ch == 'g':
                Servo6.SetPos(90)
                time.sleep(1)

    except KeyboardInterrupt:
        print("Ctrl + C")

    except Exception as e:
        print(str(e))

    finally:
        Servo0.Cleanup()
        Servo1.Cleanup()
        Servo2.Cleanup()
        Servo3.Cleanup()
        Servo4.Cleanup()
        Servo5.Cleanup()
        Servo6.Cleanup()
        print("exit profram")
        
