#include "hal_adc.h"
#if ADC_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
        static  interruptHandler ADC_InterruptHandler =NULL;
#endif 



static void Selaect_Conversion_Clock(adc_conversion_clock_t _Clock);
static inline void adc_input_channel_port_configure( adc_channel_select_t channel);
static inline void select_result_format(const adc_confg_t *_adc);
/**
 * @Summary Initializes the ADC
 * @Description This routine initializes the ADC.
 *              This routine must be called before any other ADC routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
 std_returntype ADC_Init(const adc_confg_t * _adc){
      std_returntype ret=E_OK;
    if(_adc==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
        /*Disable The ADC */
        ADC_CONVERTER_DISABLE();
        /* Configure the conversion clock */
        Selaect_Conversion_Clock((_adc->conversion_clock));
        /* Configure the default channel */
        ADCON0bits.CHS=_adc->adc_channel;
        adc_input_channel_port_configure(_adc->adc_channel);
        /* Configure the interrupt */
        #if ADC_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
        INTERRUPT_Golableinterruptenable() ;
        INTERRUPT_peripheralinterruptenable();
        ADC_InterrupEnable();
        ADC_InterruptFlagClear();
        ADC_InterruptHandler=_adc->interruptHandler;
        #endif 
        /* Configure the result format */
        select_result_format(_adc);
        /* Enable the ADC */
        ADC_CONVERTER_ENABLE();
        
        
    }
    return ret;
 
 }
 /**
 * @Summary De-Initializes the ADC
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype ADC_DeInit(const adc_confg_t * _adc){
      std_returntype ret=E_OK;
    if(_adc==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
        /*Disable The ADC */
        ADC_CONVERTER_DISABLE();
        /* Configure the interrupt */
        #if ADC_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
        ADC__InterruptDisable();
        #endif 
    }
    return ret;
 
 }
/**
 * @Summary Allows selection of a channel for conversion
 * @Description This routine is used to select desired channel for conversion.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype ADC_SelectChannel(const adc_confg_t *_adc, adc_channel_select_t channel){
      std_returntype ret=E_OK;
    if(_adc==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
         ADCON0bits.CHS=channel;
        adc_input_channel_port_configure(channel);
        
    }
    return ret;
 
 }
/**
 * @Summary Starts conversion
 * @Description This routine is used to start conversion of desired channel.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype ADC_StartConversion(const adc_confg_t *_adc){
      std_returntype ret=E_OK;
    if(_adc==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
        __delay_us(30);
        ADC_START_CONVERSION();
        
    }
    return ret;
 
 }
/**
 * @Summary Returns true when the conversion is completed otherwise false.
 * @Description This routine is used to determine if conversion is completed.
 *              When conversion is complete routine returns true. It returns false otherwise.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 *                ADC_StartConversion() should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_status The conversion status
 *          true  - If conversion is complete
 *          false - If conversion is not completed
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype ADC_IsConversionDone(const adc_confg_t *_adc, uint8 *conversion_status){
      std_returntype ret=E_OK;
    if(_adc==NULL || conversion_status==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
        *conversion_status=(uint8)(!(ADC_CONVERSION_STATUS()));
        
    }
    return ret;
 
 }
/**
 * @Summary Returns the ADC conversion value.
 * @Description This routine is used to get the analog to digital converted value.
 *              This routine gets converted values from the channel specified.
 * @Preconditions   This routine returns the conversion value only after the conversion is complete.
 *                  Completion status can be checked using ADC_IsConversionDone() routine.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype ADC_GetConversionResult(const adc_confg_t *_adc, adc_result_t *conversion_result){
      std_returntype ret=E_OK;
    if(_adc==NULL || conversion_result==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
        if(ADC_RESULT_RIGHT==_adc->result_format){
            *conversion_result = (adc_result_t)((ADRESH << 8)+ADRESL);
        }
        else if(ADC_RESULT_LEFT==_adc->result_format){
            *conversion_result = (adc_result_t)(((ADRESH << 8)+ADRESL) >> 6);
        }
        else {
            *conversion_result = (adc_result_t)((ADRESH << 8)+ADRESL);
        }

        
    }
    return ret;
 
 }
/**
 * 
 * @param _adc
 * @param channel
 * @param conversion_result
 * @return 
 */
std_returntype ADC_GetConversion_Blocking(const adc_confg_t *_adc, adc_channel_select_t channel, 
                                 adc_result_t *conversion_result){
 
      std_returntype ret=E_OK;
      uint8 l_convesion_status=ZERO_INT;
    if(_adc==NULL || conversion_result==NULL)
    {
        ret=E_NOT_OK;
    }
    else
    {
        /*select channel*/
       ret = ADC_SelectChannel(_adc,channel);
       /*start conversion*/ 
       ret = ADC_StartConversion(_adc);
       /*check conversion if complete */
       while(ADC_CONVERSION_STATUS());
       ret = ADC_GetConversionResult(_adc,conversion_result);
       
    }
    return ret; 
 }
/**
 * 
 * @param _adc
 * @param channel
 * @param conversion_result
 * @return 
 */
std_returntype ADC_StartConversion_Interrupt(const adc_confg_t *_adc, adc_channel_select_t channel){
 
      std_returntype ret=E_OK;
      uint8 l_convesion_status=ZERO_INT;
    if(_adc==NULL )
    {
        ret=E_NOT_OK;
    }
    else
    {
        /*select channel*/
       ret = ADC_SelectChannel(_adc,channel);
       /*start conversion*/ 
       ret = ADC_StartConversion(_adc);
       /*check conversion if complete */
       
     
       
    }
    return ret; 
 }

static inline void adc_input_channel_port_configure( adc_channel_select_t channel){
    
    switch(channel)
    {
        case ADC_CHANNEL_AN0: SET_BIT(TRISA,_TRISA_TRISA0_POSN ); break;
        case ADC_CHANNEL_AN1: SET_BIT(TRISA,_TRISA_TRISA1_POSN ); break;
        case ADC_CHANNEL_AN2: SET_BIT(TRISA,_TRISA_TRISA2_POSN ); break;
        case ADC_CHANNEL_AN3: SET_BIT(TRISA,_TRISA_TRISA3_POSN ); break;
        case ADC_CHANNEL_AN4: SET_BIT(TRISA,_TRISA_TRISA4_POSN ); break;
        case ADC_CHANNEL_AN5: SET_BIT(TRISE,_TRISA_TRISA0_POSN ); break;
        case ADC_CHANNEL_AN6: SET_BIT(TRISE,_TRISA_TRISA1_POSN ); break;
        case ADC_CHANNEL_AN7: SET_BIT(TRISE,_TRISA_TRISA2_POSN ); break;
    }
    


}
static inline void select_result_format(const adc_confg_t *_adc){
    if(ADC_RESULT_RIGHT==_adc->result_format){
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT==_adc->result_format){
        ADC_RESULT_LEFT_FORMAT();
    }
    else {
        ADC_RESULT_RIGHT_FORMAT();
    }

}
static void Selaect_Conversion_Clock(adc_conversion_clock_t _Clock){

     
        switch(_Clock){
            
            case ADC_CONVERSION_CLOCK_FOCS_DIV_2:ADC_CONVERSION_CLOCK_FOCS_DIV_2();    break;
            case ADC_CONVERSION_CLOCK_FOCS_DIV_8:ADC_CONVERSION_CLOCK_FOCS_DIV_8();    break;
            case ADC_CONVERSION_CLOCK_FOCS_DIV_32:ADC_CONVERSION_CLOCK_FOCS_DIV_32();  break;
            case ADC_CONVERSION_CLOCK_FOCS_DIV_FRC:ADC_CONVERSION_CLOCK_FOCS_DIV_FCR();break;
            case ADC_CONVERSION_CLOCK_FOCS_DIV_4:ADC_CONVERSION_CLOCK_FOCS_DIV_4();    break;
            case ADC_CONVERSION_CLOCK_FOCS_DIV_16:ADC_CONVERSION_CLOCK_FOCS_DIV_16();  break;
            case ADC_CONVERSION_CLOCK_FOCS_DIV_64:ADC_CONVERSION_CLOCK_FOCS_DIV_64();  break;
            default:{/*nothing*/}; 
        }    
}
void ADC_ISR(){
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler)
        ADC_InterruptHandler();

}



