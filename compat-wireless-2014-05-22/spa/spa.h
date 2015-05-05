#ifndef _SPA_H
#define _SPA_H

#include <linux/gpio.h>
#include <asm/mach-ath79/ar71xx_regs.h>
#include <asm/mach-ath79/ath79.h>

static DEFINE_SPINLOCK(ath79_gpio_lock);
enum beam_number {
        beam_omni=0,
        beam_1,
        beam_2,
        beam_3,
        beam_4
};

static inline void spa_write_io(int bit_io_20,int bit_io_21,int bit_io_22,int bit_io_23)
{
        gpio_set_value(20,bit_io_20);
        gpio_set_value(21,bit_io_21);
        gpio_set_value(22,bit_io_22);
        gpio_set_value(23,bit_io_23);
}

static inline void spa_gpio(u8 beam_number)
{
        switch (beam_number)
        {
           case beam_1:
                 spa_write_io(0,0,1,1);
                 break;
           case beam_2:
                 spa_write_io(1,0,0,1);
                 break;
           case beam_3:
                 spa_write_io(1,1,0,0);
                 break;
           case beam_4:
                 spa_write_io(0,1,1,0);
                 break;
           case beam_omni:
           default:
                 spa_write_io(0,0,0,0);
                 break; 
        }
}

static inline int setup_gpio (unsigned offset){

	void __iomem *base = ath79_gpio_base;
	unsigned long flags;
	u32 out;
	
	spin_lock_irqsave(&ath79_gpio_lock, flags);
	out = __raw_readl(base + AR71XX_GPIO_REG_OE);
        //printk(KERN_INFO "Current GPIO_OE Value, %d\n",out);
	/* __raw_writel( | (1 << offset),
		     base + AR71XX_GPIO_REG_OE);*/
        __raw_writel( out| (1 << offset),
		     base + AR71XX_GPIO_REG_OE);

	spin_unlock_irqrestore(&ath79_gpio_lock, flags);

	return 0;
}

static inline void spa_setup_io(void)
{ 
        int gpio_err;
        gpio_err = setup_gpio (20);
	gpio_err = setup_gpio (21);
	gpio_err = setup_gpio (22);
	gpio_err = setup_gpio (23);
	               
	if (!gpio_err) {
		gpio_set_value(20,1);
		gpio_set_value(21,1);
		gpio_set_value(22,1);
		gpio_set_value(23,1);
	}
}
#endif //spa.h
