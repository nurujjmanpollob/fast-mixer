package com.bluehub.fastmixer.common.dependencyinjection.presentation

import com.bluehub.fastmixer.common.utils.DialogManager
import dagger.Module
import dagger.Provides

@Module
class PresentationModule {
    @Provides
    fun dialogManager(): DialogManager = DialogManager.create()
}