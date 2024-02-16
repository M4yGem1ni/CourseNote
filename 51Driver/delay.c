/**
	* @brief	延时函数,单位为1ms 
    * @param	xms(延时时间)
    * @retval	无
    */
void Delay(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;
	while (xms)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
}